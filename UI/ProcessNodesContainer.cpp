//
// Created by 19956875375 on 2021/12/15.
//

#include "ProcessNodesContainer.h"

ProcessNodesContainer::ProcessNodesContainer(QWidget *parent) {
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Plain);
    setMaximumWidth(600);
    setMinimumWidth(400);
//    resize(600,1000);

    nodesScrollArea = new QScrollArea(this);
    nodesScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    nodesScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    nodesScrollArea->setFixedSize(width(), height());

    nodesScrollContainer = new QFrame(nodesScrollArea);
    nodesScrollArea->setWidget(nodesScrollContainer);

    nodesScrollLayout = new QVBoxLayout();
    nodesScrollLayout->setContentsMargins(30,0,30,0);
    nodesScrollLayout->setSpacing(20);
    nodesScrollLayout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    nodesScrollContainer->setLayout(nodesScrollLayout);

    int menuHeight = 50;
    auto nodeMenuLabel = new QLabel(nodesScrollContainer);
    nodeMenuLabel->setStyleSheet("border: none;");
    nodeMenuLabel->setText("Node Editor");
    nodeMenuLabel->setFixedHeight(menuHeight);
    nodeMenuLabel->adjustSize();
    nodeMenuLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    QFont font = nodeMenuLabel->font();
    font.setPointSize(20);
    font.setBold(true);
    nodeMenuLabel->setFont(font);
    nodeMenuButton = new NPushButtonExtend(nodesScrollContainer);
    nodeMenuButton->SetMenuButton(0);
    auto ic = QIcon(getIconFilePath(IC_ADD));
    nodeMenuButton->setIconSize(QSize(20,20));
    nodeMenuButton->setIcon(ic);
    nodeMenuButton->setFixedHeight(menuHeight);
    connect(nodeMenuButton, &NPushButtonExtend::signalMenuClicked, this,
            [&](const QString& nodeString) -> void {
                cout<< nodeString.toStdString() << endl;
                auto nodeWrapperMap = nodeManger.getNodes();
                auto& nodeWrapper = *new NodeWrapper(nodeWrapperMap.find(nodeString.toStdString())->second);
                auto node = nodeWrapper.getBaseNode();
                nodeManger.addShownNode(nodeWrapper, nodeManger.getShownNodes().size());
                const AbsNode& baseNode = nodeWrapper.getBaseNode();
                auto nodeFrame = createNodeFactory(baseNode);
                nodesScrollLayout->addWidget(nodeFrame);
            }
    );
    nodesMenuLayout = new QHBoxLayout();
    nodesMenuLayout->setContentsMargins(0,0,0,0);
    auto nodesMenuSubLayout = new QHBoxLayout();
    nodesMenuSubLayout->setContentsMargins(0,0,0,0);
    nodesMenuSubLayout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Expanding));
    nodesMenuSubLayout->addWidget(nodeMenuButton);
    nodesMenuSubLayout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    nodesMenuLayout->addWidget(nodeMenuLabel);
    nodesMenuLayout->addLayout(nodesMenuSubLayout);
    nodesMenuLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    nodesScrollLayout->addLayout(nodesMenuLayout);
    nodesScrollContainer->setFixedHeight(menuHeight);

//    添加输出路径
    auto dirHeight = 40;
    auto nodesSaveDir = createSaveDir(dirHeight);
    nodesScrollLayout->addLayout(nodesSaveDir);

    nodesScrollContainer->setFixedHeight(nodesScrollContainer->height() + dirHeight);
    parseNodeMenu();
    nodesScrollContainer->setFixedHeight(nodesScrollContainer->height() + 30);

    auto startHeight = 40;
    auto startLayout = createStartLayout(startHeight);
    startLayout->setGeometry(QRect(0,height() - 40,width(), 40));
    startButton->show();
}

void ProcessNodesContainer::resizeEvent(QResizeEvent *event) {
    nodesScrollArea->setFixedSize(size());
    nodesScrollContainer->setFixedWidth(width());
    startButton->setGeometry(QRect(20,height() - 40,startButton->width(), startButton->height()));
}

void ProcessNodesContainer::parseNodeMenu() {
    auto nodeWrapperMap = nodeManger.getNodes();
    auto nodeWrapperItem = nodeWrapperMap.cbegin();
    for(; nodeWrapperItem!=nodeWrapperMap.cend(); ++nodeWrapperItem) {
        nodeMenuButton->AddMenuItem(QString::fromStdString(nodeWrapperItem->first), false, true);
    }
}

QFrame* ProcessNodesContainer::createNodeFactory(const AbsNode &node) {
//  定义node GUI
    auto& nodeContainer = *new QFrame();
    nodeContainer.setObjectName("nodeContainer");
    //设置具体阴影
    auto *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 5);
    //阴影颜色
    shadow_effect->setColor(Qt::darkGray);
    //阴影半径
    shadow_effect->setBlurRadius(8);
    nodeContainer.setGraphicsEffect(shadow_effect);
    nodeContainer.setStyleSheet(
            " #nodeContainer { background-color: white; border: 1px solid lightgray; border-radius: 5px; }"
            "#nodeContainer > * {border: 1px solid gray; border-radius: 5px; padding: 5px; } "
    );
    nodeContainer.setFrameShape(QFrame::StyledPanel);
    nodeContainer.setFrameShadow(QFrame::Plain);
    nodeContainer.setFixedHeight(0);
    nodeContainer.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    auto nodeLayout = new QVBoxLayout();
    nodeLayout->setContentsMargins(10,10,10,10);
    nodeLayout->setSpacing(10);
    nodeContainer.setLayout(nodeLayout);

    int sH = 15; int mH = 33; int lH = 60;
    int nodeHeight = 0;

//  添加title
    nodeLayout->addLayout(createNodeTitle(nodeContainer, QString::fromStdString(node.getDisplayName()), mH));
    nodeHeight += mH;

//  遍历control list，构建node
    auto controlList = node.getControls();
    auto nodeName = node.getDisplayName();
    auto control = controlList.begin();
    for(; control!=controlList.end(); ++control) {
        auto controlLayout = new QHBoxLayout();
        controlLayout->setAlignment(Qt::AlignLeft);
        controlLayout->setSpacing(0);
        controlLayout->setContentsMargins(0,0,0,0);

        auto layout = new QHBoxLayout();
        layout->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
        layout->setSpacing(0);
        layout->setContentsMargins(0,0,0,0);
//  根据control类型，添加子组件
        switch (control->getType()) {
            case SLIDER: {
                auto& pSlider = *new QSlider();
                auto& sliderControl = control->getSliderControl();
                auto range = sliderControl.getRange();
                auto step = (range.second - range.first) / 20;
                pSlider.setStyleSheet("border: none;");
                pSlider.setOrientation(Qt::Horizontal);  // 水平方向
                pSlider.setRange(range.first, range.second);
                pSlider.setSingleStep(step); // 步长
                pSlider.setTracking(true);
                auto& spinBox = *new QSpinBox();
                spinBox.setRange(range.first, range.second);
                spinBox.setValue(range.first);
                auto sliderlayout = new QHBoxLayout();
                sliderlayout->setSpacing(5);
                sliderlayout->setContentsMargins(0,0,0,0);
                sliderlayout->setAlignment(Qt::AlignCenter);
                sliderlayout->addWidget(&spinBox,1);
                sliderlayout->addWidget(&pSlider,3);
                connect(&pSlider, &QSlider::valueChanged, this,
                        [&](int curValue) -> void {
                            sliderControl.setValue(curValue);
                            spinBox.setValue(curValue);
                            cout << sliderControl.getValue() << endl;
                        }
                );
                connect(&spinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
                        [&](int curValue) -> void {
                            pSlider.setValue(curValue);
                        }
                );
                layout->addLayout(sliderlayout);
                controlLayout->addWidget(createControlName(QString::fromStdString(sliderControl.getDisplayName()),mH));
                controlLayout->addLayout(layout);
                nodeLayout->addLayout(controlLayout);
                nodeHeight += mH;
                break;
            }
            case DIR_FIELD: {
                //  自定义widget，显示路径
                auto& dirText = *new QLineEdit();
                dirText.setFixedHeight(mH);
                auto& dirControl = control->getDirectoryFieldControl();
                auto dirButton = new QPushButton();
                dirButton->setFixedHeight(mH);
                dirButton->setIcon(QIcon(getIconFilePath(IC_DIR)));
                auto dirLayout = new QHBoxLayout();
                dirLayout->setSpacing(10);
                dirLayout->setContentsMargins(0,0,0,0);
                dirLayout->addWidget(&dirText);
                dirLayout->addWidget(dirButton);
                connect(dirButton, &QPushButton::clicked, this,
                        [&](int curValue) -> void {
                            auto fileText = QFileDialog::getOpenFileName(this, "选择文件","");
                            dirText.setText(fileText);
                            dirControl.setDir(fileText.toStdString());
                        }
                );
                layout->addLayout(dirLayout);
                controlLayout->addWidget(createControlName(QString::fromStdString(dirControl.getDisplayName()),mH));
                controlLayout->addLayout(layout);
                nodeLayout->addLayout(controlLayout);
                nodeHeight += mH;
                break;
            }
            case COMBO_BOX: {
                auto comboBox = new QComboBox();
                auto& comboBoxControl = control->getComboBoxControl();
                auto items = comboBoxControl.getOptionList();
                for (auto & item : items) {
                    auto text = QString::fromStdString(item);
                    comboBox->addItem(text,"");
                }
                comboBox->setFixedHeight(mH);
                comboBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
                comboBox->setCurrentIndex(0);
                connect(comboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,
                        [&comboBoxControl](int curIndex) -> void {
                            comboBoxControl.setSelected(curIndex);
                        }
                );
                layout->addWidget(comboBox);
                controlLayout->addWidget(createControlName(QString::fromStdString(comboBoxControl.getDisplayName()),mH));
                controlLayout->addLayout(layout);
                nodeLayout->addLayout(controlLayout);
                nodeHeight += mH;
                break;
            }
            case BUTTON: {
                auto button = new QPushButton();
                auto& buttonControl = control->getButtonControl();
                auto iconFilePath = getIconFilePath(buttonControl.getIconEnum());
                button->setStyleSheet("border: none;");
                button->setFixedHeight(mH);
                button->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
                button->setIconSize(QSize(20,20));
                button->setIcon(QIcon(iconFilePath));
                connect(button, &QPushButton::clicked, this,
                        [&]() -> void {
//                         删除当前的node
                            nodeContainer.setParent(nullptr);
                            nodesScrollLayout->removeWidget(&nodeContainer);
                            nodesScrollContainer->setFixedHeight(nodesScrollContainer->height() - nodeContainer.height() - nodesScrollLayout->spacing());
                            cout<< "click button" << endl;
                        }
                );
                auto buttonLayout = new QHBoxLayout();
                buttonLayout->setAlignment(Qt::AlignRight);
                buttonLayout->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding));
                buttonLayout->addWidget(button);
                layout->addLayout(buttonLayout);
                controlLayout->addWidget(createControlName(QString::fromStdString(buttonControl.getDisplayName()),mH));
                controlLayout->addLayout(layout);
                nodeLayout->addLayout(controlLayout);
                nodeHeight += mH;
                break;
            }
            case CHECKBOX: {
                auto checkBox = new QCheckBox();
                auto& checkBoxControl = control->getCheckboxControl();
                auto text = QString::fromStdString(checkBoxControl.getDisplayName());
                checkBox->setFixedHeight(mH);
                checkBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
                checkBox->setText(text);
                checkBox->setEnabled(true);
                checkBox->setCheckState(Qt::CheckState::Unchecked);
                checkBox->setTristate(false);
                connect(checkBox, &QCheckBox::stateChanged, this,
                        [&checkBoxControl](int curState) -> void {
                            if (curState == Qt::CheckState::Checked) {
                                checkBoxControl.setChecked(true);
                            } else {
                                checkBoxControl.setChecked(false);
                            }
                            cout<< "check box cur state: " << curState << endl;
                        }
                );
                layout->addWidget(checkBox);
                controlLayout->addWidget(createControlName(QString::fromStdString(checkBoxControl.getDisplayName()),mH));
                controlLayout->addLayout(layout);
                nodeLayout->addLayout(controlLayout);
                nodeHeight += mH;
                break;
            }
            case SPIN_BOX_I: {
                auto spinBox = new QSpinBox();
                auto spinBoxControl = control->template getSpinBoxControl<int>();
                auto range = spinBoxControl.getRange();
                auto step = (range.second - range.first) / 100;
                if (step < 1) step = 1;
                spinBox->setFixedHeight(mH);
                spinBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
                spinBox->setRange(range.first, range.second);
                spinBox->setSingleStep(1);
                spinBox->setValue(spinBoxControl.getValue());
                connect(spinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
                        [&spinBoxControl](int curValue) -> void {
                            spinBoxControl.setValue(curValue);
                            cout<< curValue << endl;
                        }
                );
                layout->addWidget(spinBox);
                controlLayout->addWidget(createControlName(QString::fromStdString(spinBoxControl.getDisplayName()),mH));
                controlLayout->addLayout(layout);
                nodeLayout->addLayout(controlLayout);
                nodeHeight += mH;
                break;
            }
            case SPIN_BOX_F: {
                auto spinBox = new QDoubleSpinBox();
                auto spinBoxControl = control->template getSpinBoxControl<float>();
                auto range = spinBoxControl.getRange();
                auto step = (range.second - range.first) / 100;
                if (step < 1) step = 1.0;
                spinBox->setFixedHeight(mH);
                spinBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
                spinBox->setRange(range.first, range.second);
                spinBox->setSingleStep(step);
                spinBox->setValue(spinBoxControl.getValue());
                connect(spinBox, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this,
                        [&spinBoxControl](double curValue) -> void {
                            spinBoxControl.setValue((float)curValue);
                            cout<< curValue << endl;
                        }
                );
                layout->addWidget(spinBox);
                controlLayout->addWidget(createControlName(QString::fromStdString(spinBoxControl.getDisplayName()),mH));
                controlLayout->addLayout(layout);
                nodeLayout->addLayout(controlLayout);
                nodeHeight += mH;
                break;
            }
            case COMPOSITE: {
                auto compositeControl = createCompositeControl(control->getCompositeControl());
                auto height = compositeControl->height();
                layout->addWidget(compositeControl);
//                controlLayout->addWidget(createControlName(QString::fromStdString(control->getCompositeControl().getDisplayName()),height));
                controlLayout->addLayout(layout);
                nodeLayout->addLayout(controlLayout);
                nodeHeight += height;
                break;
            }
            case TRIPLE_SPIN: {
                auto tripleControl = control->getTripleSpinControl();
                auto tripleLayout = new QHBoxLayout();
                tripleLayout->setContentsMargins(0,0,0,0);
                tripleLayout->setSpacing(10);
                tripleLayout->addLayout(createSingleTripple(tripleControl.getSpinOf(TripleSpinControl::ONE), lH));
                tripleLayout->addLayout(createSingleTripple(tripleControl.getSpinOf(TripleSpinControl::TWO), lH));
                tripleLayout->addLayout(createSingleTripple(tripleControl.getSpinOf(TripleSpinControl::THREE), lH));
                layout->addLayout(tripleLayout);
                controlLayout->addWidget(createControlName(QString::fromStdString(tripleControl.getDisplayName()),lH));
                controlLayout->addLayout(layout);
                nodeLayout->addLayout(controlLayout);
                nodeHeight += lH;
                break;
            }
            case MULTI_TYPE: {
                auto multiWidget = createMultiControl(control->getMultiTypeControl(),nodeContainer);
                layout->addWidget(multiWidget);
                controlLayout->addLayout(layout);
                nodeLayout->addLayout(controlLayout);
                nodeHeight += multiWidget->height();
                break;
            }
            default:
                break;
        }
    }

//  构建尾部
    nodeLayout->addLayout(createNodeTail(node, lH));
    nodeHeight += lH;

    nodeContainer.setFixedHeight(nodeHeight + nodeLayout->spacing() * (nodeLayout->count() - 1) + 20);
    nodesScrollContainer->setFixedHeight(
            nodesScrollContainer->height() +
            nodeContainer.height() +
            nodesScrollLayout->spacing());
    return &nodeContainer;
}

QFrame *ProcessNodesContainer::createCompositeControl(const CompositeControl &compositeControl) {
    //  定义node GUI
    auto& nodeContainer = *new QFrame();
    nodeContainer.setObjectName("nodeContainer");
    nodeContainer.setStyleSheet(
            " #nodeContainer { background-color: white; border: 1px solid lightgray; border-radius: 5px; }"
            "#nodeContainer > * {border: 1px solid gray; border-radius: 5px;padding: 5px } "
    );
    nodeContainer.setFrameShape(QFrame::StyledPanel);
    nodeContainer.setFrameShadow(QFrame::Plain);
    nodeContainer.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    auto nodeLayout = new QVBoxLayout();
    nodeLayout->setContentsMargins(10,10,10,10);
    nodeLayout->setSpacing(10);
    nodeContainer.setLayout(nodeLayout);

    int nodeHeight = 0;
    int sH = 15; int mH = 33; int lH = 60;

    auto titleLayout = new QHBoxLayout();
    titleLayout->setContentsMargins(0,0,0,0);
    titleLayout->setSpacing(0);
    titleLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    titleLayout->addWidget(createControlName(QString::fromStdString(compositeControl.getDisplayName()), mH, true));
    nodeLayout->addLayout(titleLayout);
    nodeHeight += mH;

//  遍历control list，构建node
    auto controlList = compositeControl.getSubControlList();
    auto nodeName = compositeControl.getDisplayName();
    auto control = controlList.begin();
    for(; control!=controlList.end(); ++control) {
        auto controlLayout = new QHBoxLayout();
        controlLayout->setAlignment(Qt::AlignLeft);
        controlLayout->setSpacing(0);
        controlLayout->setContentsMargins(0,0,0,0);

        auto layout = new QHBoxLayout();
        layout->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
        layout->setSpacing(0);
        layout->setContentsMargins(0,0,0,0);
//  根据control类型，添加子组件
        switch (control->getType()) {
            case SLIDER: {
                auto& pSlider = *new QSlider();
                auto& sliderControl = control->getSliderControl();
                auto range = sliderControl.getRange();
                auto step = (range.second - range.first) / 20;
                pSlider.setStyleSheet("border: none;");
                pSlider.setOrientation(Qt::Horizontal);  // 水平方向
                pSlider.setRange(range.first, range.second);
                pSlider.setSingleStep(step); // 步长
                pSlider.setTracking(true);
                auto& spinBox = *new QSpinBox();
                spinBox.setRange(range.first, range.second);
                spinBox.setValue(range.first);
                auto sliderlayout = new QHBoxLayout();
                sliderlayout->setSpacing(5);
                sliderlayout->setContentsMargins(0,0,0,0);
                sliderlayout->setAlignment(Qt::AlignCenter);
                sliderlayout->addWidget(&spinBox,1);
                sliderlayout->addWidget(&pSlider,3);
                connect(&pSlider, &QSlider::valueChanged, this,
                        [&](int curValue) -> void {
                            sliderControl.setValue(curValue);
                            spinBox.setValue(curValue);
                            cout << sliderControl.getValue() << endl;
                        }
                );
                connect(&spinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
                        [&](int curValue) -> void {
                            pSlider.setValue(curValue);
                        }
                );
                layout->addLayout(sliderlayout);
                controlLayout->addWidget(createControlName(QString::fromStdString(sliderControl.getDisplayName()),mH));
                controlLayout->addLayout(layout);
                nodeLayout->addLayout(controlLayout);
                nodeHeight += mH;
                break;
            }
            case DIR_FIELD: {
                //  自定义widget，显示路径
                auto& dirText = *new QLineEdit();
                dirText.setFixedHeight(mH);
                auto& dirControl = control->getDirectoryFieldControl();
                auto dirButton = new QPushButton();
                dirButton->setFixedHeight(mH);
                dirButton->setIcon(QIcon(getIconFilePath(IC_DIR)));
                auto dirLayout = new QHBoxLayout();
                dirLayout->setSpacing(10);
                dirLayout->setContentsMargins(0,0,0,0);
                dirLayout->addWidget(&dirText);
                dirLayout->addWidget(dirButton);
                connect(dirButton, &QPushButton::clicked, this,
                        [&](int curValue) -> void {
                            auto fileText = QFileDialog::getOpenFileName(this, "选择文件","");
                            dirText.setText(fileText);
                            dirControl.setDir(fileText.toStdString());
                        }
                );
                layout->addLayout(dirLayout);
                controlLayout->addWidget(createControlName(QString::fromStdString(dirControl.getDisplayName()),mH));
                controlLayout->addLayout(layout);
                nodeLayout->addLayout(controlLayout);
                nodeHeight += mH;
                break;
            }
            case COMBO_BOX: {
                auto comboBox = new QComboBox();
                auto& comboBoxControl = control->getComboBoxControl();
                auto items = comboBoxControl.getOptionList();
                for (auto & item : items) {
                    auto text = QString::fromStdString(item);
                    comboBox->addItem(text,"");
                }
                comboBox->setFixedHeight(mH);
                comboBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
                comboBox->setCurrentIndex(0);
                connect(comboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,
                        [&comboBoxControl](int curIndex) -> void {
                            comboBoxControl.setSelected(curIndex);
                        }
                );
                layout->addWidget(comboBox);
                controlLayout->addWidget(createControlName(QString::fromStdString(comboBoxControl.getDisplayName()),mH));
                controlLayout->addLayout(layout);
                nodeLayout->addLayout(controlLayout);
                nodeHeight += mH;
                break;
            }
            case BUTTON: {
                auto button = new QPushButton();
                auto& buttonControl = control->getButtonControl();
                auto iconFilePath = getIconFilePath(buttonControl.getIconEnum());
                button->setStyleSheet("border: none;");
                button->setFixedHeight(mH);
                button->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
                button->setIconSize(QSize(50,30));
                button->setIcon(QIcon(iconFilePath));
                connect(button, &QPushButton::clicked, this,
                        [&]() -> void {
//                         删除当前的node
                            nodeContainer.setParent(nullptr);
                            nodesScrollLayout->removeWidget(&nodeContainer);
                            nodesScrollContainer->setFixedHeight(nodesScrollContainer->height() - nodeContainer.height() - nodesScrollLayout->spacing());
                            cout<< "click button" << endl;
                        }
                );
                auto buttonLayout = new QHBoxLayout();
                buttonLayout->setAlignment(Qt::AlignRight);
                buttonLayout->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding));
                buttonLayout->addWidget(button);
                layout->addLayout(buttonLayout);
                controlLayout->addWidget(createControlName(QString::fromStdString(buttonControl.getDisplayName()),mH));
                controlLayout->addLayout(layout);
                nodeLayout->addLayout(controlLayout);
                nodeHeight += mH;
                break;
            }
            case CHECKBOX: {
                auto checkBox = new QCheckBox();
                auto& checkBoxControl = control->getCheckboxControl();
                auto text = QString::fromStdString(checkBoxControl.getDisplayName());
                checkBox->setFixedHeight(mH);
                checkBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
                checkBox->setText(text);
                checkBox->setEnabled(true);
                checkBox->setCheckState(Qt::CheckState::Unchecked);
                checkBox->setTristate(false);
                connect(checkBox, &QCheckBox::stateChanged, this,
                        [&checkBoxControl](int curState) -> void {
                            if (curState == Qt::CheckState::Checked) {
                                checkBoxControl.setChecked(true);
                            } else {
                                checkBoxControl.setChecked(false);
                            }
                            cout<< "check box cur state: " << curState << endl;
                        }
                );
                layout->addWidget(checkBox);
                controlLayout->addWidget(createControlName(QString::fromStdString(checkBoxControl.getDisplayName()),mH));
                controlLayout->addLayout(layout);
                nodeLayout->addLayout(controlLayout);
                nodeHeight += mH;
                break;
            }
            case SPIN_BOX_I: {
                auto spinBox = new QSpinBox();
                auto spinBoxControl = control->getSpinBoxControl<int>();
                auto range = spinBoxControl.getRange();
                auto step = (range.second - range.first) / 100;
                if (step < 1) step = 1;
                spinBox->setFixedHeight(mH);
                spinBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
                spinBox->setRange(range.first, range.second);
                spinBox->setSingleStep(1);
                spinBox->setValue(spinBoxControl.getValue());
                connect(spinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
                        [&spinBoxControl](int curValue) -> void {
                            spinBoxControl.setValue(curValue);
                            cout<< curValue << endl;
                        }
                );
                layout->addWidget(spinBox);
                controlLayout->addWidget(createControlName(QString::fromStdString(spinBoxControl.getDisplayName()),mH));
                controlLayout->addLayout(layout);
                nodeLayout->addLayout(controlLayout);
                nodeHeight += mH;
                break;
            }
            case SPIN_BOX_F: {
                auto spinBox = new QDoubleSpinBox();
                auto spinBoxControl = control->template getSpinBoxControl<float>();
                auto range = spinBoxControl.getRange();
                auto step = (range.second - range.first) / 100;
                if (step < 1) step = 1.0;
                spinBox->setFixedHeight(mH);
                spinBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
                spinBox->setRange(range.first, range.second);
                spinBox->setSingleStep(step);
                spinBox->setValue(spinBoxControl.getValue());
                connect(spinBox, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this,
                        [&spinBoxControl](double curValue) -> void {
                            spinBoxControl.setValue((float)curValue);
                            cout<< curValue << endl;
                        }
                );
                layout->addWidget(spinBox);
                controlLayout->addWidget(createControlName(QString::fromStdString(spinBoxControl.getDisplayName()),mH));
                controlLayout->addLayout(layout);
                nodeLayout->addLayout(controlLayout);
                nodeHeight += mH;
                break;
            }
            case TRIPLE_SPIN: {
                auto tripleControl = control->getTripleSpinControl();
                auto tripleLayout = new QHBoxLayout();
                tripleLayout->setContentsMargins(0,0,0,0);
                tripleLayout->setSpacing(10);
                tripleLayout->addLayout(createSingleTripple(tripleControl.getSpinOf(TripleSpinControl::ONE), lH));
                tripleLayout->addLayout(createSingleTripple(tripleControl.getSpinOf(TripleSpinControl::TWO), lH));
                tripleLayout->addLayout(createSingleTripple(tripleControl.getSpinOf(TripleSpinControl::THREE), lH));
                layout->addLayout(tripleLayout);
                controlLayout->addWidget(createControlName(QString::fromStdString(tripleControl.getDisplayName()),lH));
                controlLayout->addLayout(layout);
                nodeLayout->addLayout(controlLayout);
                nodeHeight += lH;
                break;
            }
            default:
                break;
        }
    }
    nodeContainer.setFixedHeight(nodeHeight + nodeLayout->spacing() * (nodeLayout->count() - 1) + 20);
    nodesScrollContainer->setFixedHeight(
            nodesScrollContainer->height() +
            nodeContainer.height() +
            nodesScrollLayout->spacing());
    return &nodeContainer;
}

QFrame *ProcessNodesContainer::createMultiControl(MultiTypeControl& multiTypeControl, QFrame& nodeContainer) {
    //  定义node GUI
    auto& multiContainer = *new QFrame();
    multiContainer.setObjectName("multiContainer");
    multiContainer.setStyleSheet(
            " #multiContainer { background-color: white; border: 1px solid lightgray; border-radius: 5px; }"
            "#multiContainer > * {border: 1px solid gray; border-radius: 5px;padding: 5px } "
    );
    multiContainer.setFrameShape(QFrame::StyledPanel);
    multiContainer.setFrameShadow(QFrame::Plain);
    multiContainer.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    auto& multiContainerlayout = *new QVBoxLayout();
    multiContainerlayout.setContentsMargins(10,10,10,10);
    multiContainerlayout.setSpacing(10);
    multiContainer.setLayout(&multiContainerlayout);

    int headHeight = 0;
    int sH = 15; int mH = 33; int lH = 60;

    auto titleLayout = new QHBoxLayout();
    titleLayout->setContentsMargins(0,0,0,0);
    titleLayout->setSpacing(0);
    titleLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    titleLayout->addWidget(createControlName(QString::fromStdString(multiTypeControl.getDisplayName()), mH, true));
    multiContainerlayout.addLayout(titleLayout);
    headHeight += mH;

//    加载选择器
    auto selectLayout = new QHBoxLayout();
    selectLayout->setContentsMargins(0,0,0,0);
    selectLayout->setSpacing(0);
    selectLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    selectLayout->addWidget(createControlName("Choose One", mH, true));

    auto comboBox = new QComboBox();
    auto iconFilePath = getIconFilePath(IC_DEL);
    comboBox->setFixedHeight(mH);
    comboBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    auto map = multiTypeControl.getSubControlMap();
    auto iter = map.begin();
    while(iter != map.end()) {
        comboBox->addItem(QString::fromStdString(iter->first),"");
        iter++;
    }

    comboBox->setCurrentIndex(multiTypeControl.getSelectedIndex());
    auto comboLayout = new QHBoxLayout();
    comboLayout->setAlignment(Qt::AlignRight);
    comboLayout->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding));
    comboLayout->addWidget(comboBox);
    selectLayout->addLayout(comboLayout);

    multiContainerlayout.addLayout(selectLayout);
    headHeight += mH;

//  遍历control list,构建control的body
    auto& multiControlBody = *createMultiControlList(map[multiTypeControl.getSelected()]);
    multiContainerlayout.addWidget(&multiControlBody);
    multiContainer.setFixedHeight(multiControlBody.height() + headHeight +
        multiContainerlayout.spacing() * (multiContainerlayout.count() - 1) + 20);

    connect(comboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,
            [&](int curIndex) -> void {
                multiTypeControl.setSelected(multiTypeControl.getSelectedStringFromIndex(curIndex));
                auto widget = multiContainerlayout.itemAt(multiContainerlayout.count() - 1)->widget();
                widget->setParent(nullptr);
                multiContainerlayout.removeWidget(widget);
                auto map = multiTypeControl.getSubControlMap();
                auto multiControlBody_ = createMultiControlList(map[multiTypeControl.getSelected()]);
                multiContainerlayout.addWidget(multiControlBody_);
                multiContainer.setFixedHeight(multiControlBody_->height() + 66 +
                                              multiContainerlayout.spacing() * (multiContainerlayout.count() - 1) + 20);
            }
    );

    return &multiContainer;
}

QString ProcessNodesContainer::getIconFilePath(ICON icon) {
    switch (icon) {
        case IC_ADD: return QString::fromStdString("../UI_SRC/add.png");
        case IC_MINUS: return QString::fromStdString("../UI_SRC/minus.png");
        case IC_DEL: return QString::fromStdString("../UI_SRC/del.png");
        case IC_DIR: return QString::fromStdString("../UI_SRC/dir.png");
        default:return QString::fromStdString("../UI_SRC/add.png");
    }
}

QLabel *ProcessNodesContainer::createControlName(const QString &text, int height, bool isBold, int width ) {
    auto name = new QLabel();
    name->setStyleSheet("border: none;");
    name->setText(text);
    name->setFixedHeight(height);
    name->setFixedWidth(width);
    name->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    if (isBold) {
        QFont font = name->font();
        font.setBold(true);
        name->setFont(font);
    }
    return name;
}

QHBoxLayout *ProcessNodesContainer::createNodeTitle(QFrame& nodeContainer, const QString &text, int height) {
    auto titleLayout = new QHBoxLayout();
    titleLayout->setContentsMargins(0,0,0,0);
    titleLayout->setSpacing(0);
    titleLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    titleLayout->addWidget(createControlName(text, height, true));

    auto button = new QPushButton();
    auto iconFilePath = getIconFilePath(IC_DEL);
    button->setStyleSheet("border: none;");
    button->setFixedHeight(height);
    button->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    button->setIconSize(QSize(20,20));
    button->setIcon(QIcon(iconFilePath));
    connect(button, &QPushButton::clicked, this,
            [&]() -> void {
                nodeContainer.setParent(nullptr);
                nodesScrollLayout->removeWidget(&nodeContainer);
                nodesScrollContainer->setFixedHeight(nodesScrollContainer->height() - nodeContainer.height() - nodesScrollLayout->spacing());
                cout<< "click button" << endl;
            }
    );
    auto buttonLayout = new QHBoxLayout();
    buttonLayout->setAlignment(Qt::AlignRight);
    buttonLayout->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding));
    buttonLayout->addWidget(button);
    titleLayout->addLayout(buttonLayout);
    return titleLayout;
}

QVBoxLayout *ProcessNodesContainer::createNodeTail(AbsNode node, int height) {
    auto vLayout = new QVBoxLayout();
    vLayout->setContentsMargins(0,0,0,0);
    vLayout->setSpacing(0);

    auto progressBar = new QProgressBar();
    progressBar->setObjectName("progressBar");
    progressBar->setStyleSheet(
            " #progressBar { border: none; }"
    );
    progressBar->setOrientation(Qt::Horizontal);
    progressBar->setMinimum(0);
    progressBar->setMaximum(100);
    progressBar->setFixedHeight(height / 2);
    progressBar->setValue(0);
    progressBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    progressBar->setTextVisible(false);

    auto hLayout = new QHBoxLayout();
    hLayout->setContentsMargins(0,0,0,0);
    hLayout->setSpacing(0);

    auto name = new QLabel();
    name->setStyleSheet("border: none;");
    name->setText("Not running");
    name->setFixedHeight(height / 2);

    auto value = new QLabel();
    value->setStyleSheet("border: none;");
    double delta = (progressBar->value() - progressBar->minimum()) * 100.0
                               / (progressBar->maximum() - progressBar->minimum());
    value->setText(QString::fromLocal8Bit("%1%").arg(
            QString::number(delta, 'f', 1)));
    value->setFixedHeight(height / 2);

    hLayout->addWidget(name);
    hLayout->addWidget(value);
    hLayout->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding));
    vLayout->addWidget(progressBar);
    vLayout->addLayout(hLayout);
    node.addStartListener(
            [&] () -> void {

            }
    );
    node.addProgressListener(
            [&] (int curValue) -> void {
                progressBar->setValue(curValue);
                name->setText("running");
                double delta = (progressBar->value() - progressBar->minimum()) * 100.0
                               / (progressBar->maximum() - progressBar->minimum());
                value->setText(QString::fromLocal8Bit("%1%").arg(
                        QString::number(delta, 'f', 1)));
            }
    );
    node.addFinishListener(
            [&] () -> void {
                name->setText("complete");
                progressBar->setValue(progressBar->maximum());
                value->setText(QString("100%"));
            });
    return vLayout;
}

QHBoxLayout *ProcessNodesContainer::createSaveDir(int height) {
    auto hLayout = new QHBoxLayout();
    hLayout->setContentsMargins(0,0,0,0);
    hLayout->setSpacing(0);

    auto& dirText = *new QLineEdit();
    dirText.setFixedHeight(height);
    auto dirButton = new QPushButton();
    dirButton->setStyleSheet("border:none;");
    dirButton->setFixedHeight(height);
    dirButton->setIcon(QIcon(getIconFilePath(IC_DIR)));
    dirButton->setIconSize(QSize(20,20));
    auto dirLayout = new QHBoxLayout();
    dirLayout->setSpacing(10);
    dirLayout->setContentsMargins(0,0,0,0);
    dirLayout->addWidget(&dirText);
    dirLayout->addWidget(dirButton);
    connect(dirButton, &QPushButton::clicked, this,
            [&](int curValue) -> void {
                auto fileText = QFileDialog::getExistingDirectory(this, "Choose a directory","");
                dirText.setText(fileText);
                this->saveDir = fileText.toStdString();
            }
    );

    hLayout->addWidget(createControlName(QString::fromStdString("Path to save result:"),height));
    hLayout->addLayout(dirLayout);
    return hLayout;
}

QHBoxLayout *ProcessNodesContainer::createStartLayout(int height) {
    auto startLayout = new QHBoxLayout();
    startLayout->setContentsMargins(20,0,20,0);
    startLayout->setSpacing(0);
    startLayout->setAlignment(Qt::AlignCenter);

    startButton = new QPushButton(this);
    startButton->setText("Start");
    startButton->setObjectName("startbutton");
    startButton->setStyleSheet(
            " #startbutton { background-color: rgb(52,132,247); border: none; border-radius: 10px; }"
    );
    QFont font = startButton->font();
    font.setPointSize(30);
    font.setBold(false);
    startButton->setFont(font);
    startButton->setFixedHeight(height);
    startButton->raise();
    startButton->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    startLayout->addWidget(startButton);
    connect(startButton, &QPushButton::clicked, this,
            [&]() -> void {
                startButton->setText("Running");
                emit startSignal();
                cout<< "start!" << endl;
            }
    );
    return startLayout;
}

QVBoxLayout *ProcessNodesContainer::createSingleTripple(TripleSpinControl::SpinDescriptor &mstruct, int height) {
    auto vLayout = new QVBoxLayout();
    vLayout->setContentsMargins(0,0,0,0);
    vLayout->setSpacing(5);
    auto spinBox = new QSpinBox();
    auto step = (mstruct.maxValue - mstruct.minValue) / 100;
    if (step < 1) step = 1;
    spinBox->setFixedHeight(height/2);
    spinBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    spinBox->setRange(mstruct.minValue,mstruct.maxValue);
    spinBox->setSingleStep(1);
    spinBox->setValue(mstruct.value);
    connect(spinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
            [&](int curValue) -> void {
                mstruct.value = curValue;
                cout<< curValue << endl;
            }
    );
    auto name = new QLabel();
    name->setStyleSheet("border: none;");
    name->setText(QString::fromStdString(mstruct.name));
    name->setFixedHeight(height / 2 - vLayout->spacing());
    name->setAlignment(Qt::AlignHCenter);
    vLayout->addWidget(spinBox);
    vLayout->addWidget(name);
    return vLayout;
}

QFrame *ProcessNodesContainer::createMultiControlList(list<SingleControlWrapper>& controlList) {
    auto nodeContainer = new QFrame();
    nodeContainer->setObjectName("multiContainer");
    nodeContainer->setStyleSheet(" #multiContainer { background-color: white; border: none;}");
    nodeContainer->setFrameShape(QFrame::StyledPanel);
    nodeContainer->setFrameShadow(QFrame::Plain);
    nodeContainer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    auto nodeLayout = new QVBoxLayout();
    nodeLayout->setContentsMargins(0,0,0,0);
    nodeLayout->setSpacing(10);
    nodeContainer->setLayout(nodeLayout);

    int nodeHeight = 0;
    int sH = 15; int mH = 33; int lH = 60;

    for(auto control_: controlList){
        auto control = &control_;
        auto controlLayout = new QHBoxLayout();
        controlLayout->setAlignment(Qt::AlignLeft);
        controlLayout->setSpacing(0);
        controlLayout->setContentsMargins(0,0,0,0);

        auto layout = new QHBoxLayout();
        layout->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
        layout->setSpacing(0);
        layout->setContentsMargins(0,0,0,0);
//  根据control类型，添加子组件
        switch (control->getType()) {
            case SLIDER: {
                auto& pSlider = *new QSlider();
                auto& sliderControl = control->getSliderControl();
                auto range = sliderControl.getRange();
                auto step = (range.second - range.first) / 20;
                pSlider.setStyleSheet("border: none;");
                pSlider.setOrientation(Qt::Horizontal);  // 水平方向
                pSlider.setRange(range.first, range.second);
                pSlider.setSingleStep(step); // 步长
                pSlider.setTracking(true);
                auto& spinBox = *new QSpinBox();
                spinBox.setRange(range.first, range.second);
                spinBox.setValue(range.first);
                auto sliderlayout = new QHBoxLayout();
                sliderlayout->setSpacing(5);
                sliderlayout->setContentsMargins(0,0,0,0);
                sliderlayout->setAlignment(Qt::AlignCenter);
                sliderlayout->addWidget(&spinBox,1);
                sliderlayout->addWidget(&pSlider,3);
                connect(&pSlider, &QSlider::valueChanged, this,
                        [&](int curValue) -> void {
                            sliderControl.setValue(curValue);
                            spinBox.setValue(curValue);
                            cout << sliderControl.getValue() << endl;
                        }
                );
                connect(&spinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
                        [&](int curValue) -> void {
                            pSlider.setValue(curValue);
                        }
                );
                layout->addLayout(sliderlayout);
                controlLayout->addWidget(createControlName(QString::fromStdString(sliderControl.getDisplayName()),mH));
                controlLayout->addLayout(layout);
                nodeLayout->addLayout(controlLayout);
                nodeHeight += mH;
                break;
            }
            case DIR_FIELD: {
                //  自定义widget，显示路径
                auto& dirText = *new QLineEdit();
                dirText.setFixedHeight(mH);
                auto& dirControl = control->getDirectoryFieldControl();
                auto dirButton = new QPushButton();
                dirButton->setFixedHeight(mH);
                dirButton->setIcon(QIcon(getIconFilePath(IC_DIR)));
                auto dirLayout = new QHBoxLayout();
                dirLayout->setSpacing(10);
                dirLayout->setContentsMargins(0,0,0,0);
                dirLayout->addWidget(&dirText);
                dirLayout->addWidget(dirButton);
                connect(dirButton, &QPushButton::clicked, this,
                        [&](int curValue) -> void {
                            auto fileText = QFileDialog::getOpenFileName(this, "选择文件","");
                            dirText.setText(fileText);
                            dirControl.setDir(fileText.toStdString());
                        }
                );
                layout->addLayout(dirLayout);
                controlLayout->addWidget(createControlName(QString::fromStdString(dirControl.getDisplayName()),mH));
                controlLayout->addLayout(layout);
                nodeLayout->addLayout(controlLayout);
                nodeHeight += mH;
                break;
            }
            case COMBO_BOX: {
                auto comboBox = new QComboBox();
                auto& comboBoxControl = control->getComboBoxControl();
                auto items = comboBoxControl.getOptionList();
                for (auto & item : items) {
                    auto text = QString::fromStdString(item);
                    comboBox->addItem(text,"");
                }
                comboBox->setFixedHeight(mH);
                comboBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
                comboBox->setCurrentIndex(0);
                connect(comboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,
                        [&comboBoxControl](int curIndex) -> void {
                            comboBoxControl.setSelected(curIndex);
                        }
                );
                layout->addWidget(comboBox);
                controlLayout->addWidget(createControlName(QString::fromStdString(comboBoxControl.getDisplayName()),mH));
                controlLayout->addLayout(layout);
                nodeLayout->addLayout(controlLayout);
                nodeHeight += mH;
                break;
            }
            case CHECKBOX: {
                auto checkBox = new QCheckBox();
                auto& checkBoxControl = control->getCheckboxControl();
                auto text = QString::fromStdString(checkBoxControl.getDisplayName());
                checkBox->setFixedHeight(mH);
                checkBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
                checkBox->setText(text);
                checkBox->setEnabled(true);
                checkBox->setCheckState(Qt::CheckState::Unchecked);
                checkBox->setTristate(false);
                connect(checkBox, &QCheckBox::stateChanged, this,
                        [&checkBoxControl](int curState) -> void {
                            if (curState == Qt::CheckState::Checked) {
                                checkBoxControl.setChecked(true);
                            } else {
                                checkBoxControl.setChecked(false);
                            }
                            cout<< "check box cur state: " << curState << endl;
                        }
                );
                layout->addWidget(checkBox);
                controlLayout->addWidget(createControlName(QString::fromStdString(checkBoxControl.getDisplayName()),mH));
                controlLayout->addLayout(layout);
                nodeLayout->addLayout(controlLayout);
                nodeHeight += mH;
                break;
            }
            case SPIN_BOX_I: {
                auto spinBox = new QSpinBox();
                auto spinBoxControl = control->getSpinBoxControl<int>();
                auto range = spinBoxControl.getRange();
                auto step = (range.second - range.first) / 100;
                if (step < 1) step = 1;
                spinBox->setFixedHeight(mH);
                spinBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
                spinBox->setRange(range.first, range.second);
                spinBox->setSingleStep(1);
                spinBox->setValue(spinBoxControl.getValue());
                connect(spinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
                        [&spinBoxControl](int curValue) -> void {
                            spinBoxControl.setValue(curValue);
                            cout<< curValue << endl;
                        }
                );
                layout->addWidget(spinBox);
                controlLayout->addWidget(createControlName(QString::fromStdString(spinBoxControl.getDisplayName()),mH));
                controlLayout->addLayout(layout);
                nodeLayout->addLayout(controlLayout);
                nodeHeight += mH;
                break;
            }
            case SPIN_BOX_F: {
                auto spinBox = new QDoubleSpinBox();
                auto spinBoxControl = control->template getSpinBoxControl<float>();
                auto range = spinBoxControl.getRange();
                auto step = (range.second - range.first) / 100;
                if (step < 1) step = 1.0;
                spinBox->setFixedHeight(mH);
                spinBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
                spinBox->setRange(range.first, range.second);
                spinBox->setSingleStep(step);
                spinBox->setValue(spinBoxControl.getValue());
                connect(spinBox, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this,
                        [&spinBoxControl](double curValue) -> void {
                            spinBoxControl.setValue((float)curValue);
                            cout<< curValue << endl;
                        }
                );
                layout->addWidget(spinBox);
                controlLayout->addWidget(createControlName(QString::fromStdString(spinBoxControl.getDisplayName()),mH));
                controlLayout->addLayout(layout);
                nodeLayout->addLayout(controlLayout);
                nodeHeight += mH;
                break;
            }
            case TRIPLE_SPIN: {
                auto tripleControl = control->getTripleSpinControl();
                auto tripleLayout = new QHBoxLayout();
                tripleLayout->setContentsMargins(0,0,0,0);
                tripleLayout->setSpacing(10);
                tripleLayout->addLayout(createSingleTripple(tripleControl.getSpinOf(TripleSpinControl::ONE), lH));
                tripleLayout->addLayout(createSingleTripple(tripleControl.getSpinOf(TripleSpinControl::TWO), lH));
                tripleLayout->addLayout(createSingleTripple(tripleControl.getSpinOf(TripleSpinControl::THREE), lH));
                layout->addLayout(tripleLayout);
                controlLayout->addWidget(createControlName(QString::fromStdString(tripleControl.getDisplayName()),lH));
                controlLayout->addLayout(layout);
                nodeLayout->addLayout(controlLayout);
                nodeHeight += lH;
                break;
            }
            default:
                break;
        }
    }
    nodeContainer->setFixedHeight(nodeHeight + nodeLayout->spacing() * (nodeLayout->count() - 1));
    return nodeContainer;
}
