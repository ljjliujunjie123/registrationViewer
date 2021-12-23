//
// Created by 19956875375 on 2021/12/15.
//

#include "ProcessNodesContainer.h"

ProcessNodesContainer::ProcessNodesContainer(QWidget *parent) {
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Plain);
    setMaximumWidth(600);
    setMinimumWidth(400);
    nodesScrollArea = new QScrollArea(this);
    nodesScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    nodesScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    nodesScrollArea->setFixedSize(size());

    nodesScrollContainer = new QFrame(nodesScrollArea);
    nodesScrollArea->setWidget(nodesScrollContainer);

    nodesScrollLayout = new QVBoxLayout();
    nodesScrollLayout->setContentsMargins(30,0,30,0);
    nodesScrollLayout->setSpacing(20);
    nodesScrollLayout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    nodesScrollContainer->setLayout(nodesScrollLayout);

    int menuHeight = 40;
    auto nodeMenuLabel = new QLabel(nodesScrollContainer);
    nodeMenuLabel->setStyleSheet("border: none;");
    nodeMenuLabel->setText("添加Node:");
    nodeMenuLabel->setFixedHeight(menuHeight);
    nodeMenuLabel->adjustSize();
    nodeMenuLabel->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    nodeMenuButton = new NPushButtonExtend(nodesScrollContainer);
    nodeMenuButton->SetMenuButton(0);
    nodeMenuButton->setIcon(QIcon(getIconFilePath(IC_ADD)));
    nodeMenuButton->setFixedHeight(menuHeight);
    connect(nodeMenuButton, &NPushButtonExtend::signalMenuClicked, this,
            [&](const QString& nodeString) -> void {
                cout<< nodeString.toStdString() << endl;
                auto nodeWrapperMap = nodeManger.getNodes();
                auto nodeWrapper = new NodeWrapper(nodeWrapperMap.find(nodeString.toStdString())->second);
                auto node = new TestNode("adsioc","dhcasiu");
                NodeWrapper& newNodeWrapper = *new NodeWrapper(*node);
                nodeManger.addShownNode(newNodeWrapper, nodeManger.getShownNodes().size());
                const AbsNode& baseNode = newNodeWrapper.getBaseNode();
                auto nodeFrame = createNodeFactory(baseNode);
                nodesScrollLayout->addWidget(nodeFrame);
            }
    );
    nodesMenuLayout = new QHBoxLayout();
    nodesMenuLayout->setContentsMargins(0,0,0,0);
    nodesMenuLayout->addWidget(nodeMenuLabel);
    nodesMenuLayout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Expanding));
    nodesMenuLayout->addWidget(nodeMenuButton);
    nodesMenuLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    nodesScrollLayout->addLayout(nodesMenuLayout);
    nodesScrollContainer->setFixedHeight(menuHeight);
    parseNodeMenu();
    nodesScrollContainer->setFixedHeight(nodesScrollContainer->height() + 30);
}

void ProcessNodesContainer::resizeEvent(QResizeEvent *event) {
    nodesScrollArea->setFixedSize(size());
    nodesScrollContainer->setFixedWidth(width());
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
    nodeContainer.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    auto nodeLayout = new QVBoxLayout();
    nodeLayout->setContentsMargins(10,10,10,10);
    nodeLayout->setSpacing(10);
    nodeContainer.setLayout(nodeLayout);

//  遍历control list，构建node
    auto controlList = node.getControls();
    auto nodeName = node.getDisplayName();
    auto control = controlList.begin();
    int nodeHeight = 0;
    int sH = 15; int mH = 33; int lH = 60;
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

//  遍历control list，构建node
    auto controlList = compositeControl.getSubControlList();
    auto nodeName = compositeControl.getDisplayName();
    auto control = controlList.begin();
    int nodeHeight = 0;
    int sH = 15; int mH = 33; int lH = 60;
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

QString ProcessNodesContainer::getIconFilePath(ICON icon) {
    switch (icon) {
        case IC_ADD: return QString::fromStdString("../UI_SRC/add.png");
        case IC_MINUS: return QString::fromStdString("../UI_SRC/minus.png");
        case IC_DEL: return QString::fromStdString("../UI_SRC/del.png");
        case IC_DIR: return QString::fromStdString("../UI_SRC/dir.png");
        default:return QString::fromStdString("../UI_SRC/add.png");
    }
}

QLabel *ProcessNodesContainer::createControlName(const QString &text, int height, int width) {
    auto name = new QLabel();
    name->setStyleSheet("border: none;");
    name->setText(text);
    name->setFixedHeight(height);
    name->setFixedWidth(width);
    name->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    return name;
}