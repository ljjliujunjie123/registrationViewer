//
// Created by 19956875375 on 2021/12/15.
//

#include "ProcessNodesContainer.h"

ProcessNodesContainer::ProcessNodesContainer(QWidget *parent) {
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Plain);
    setMaximumWidth(600);
    setMinimumWidth(300);
    nodesScrollArea = new QScrollArea(this);
    nodesScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    nodesScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    nodesScrollArea->setFixedSize(size());

    nodesScrollContainer = new QFrame(nodesScrollArea);
    nodesScrollArea->setWidget(nodesScrollContainer);

//    spacerHLayout = new QHBoxLayout();
//    spacerHLayout->setContentsMargins(0,0,0,0);
//    spacerHLayout->setSpacing(0);
//    spacerHLayout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Expanding));
//    spacerHLayout->addWidget(nodesScrollContainer);
//    spacerHLayout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Expanding));
//    nodesScrollArea->setLayout(spacerHLayout);

    nodesScrollLayout = new QVBoxLayout();
    nodesScrollLayout->setContentsMargins(20,0,20,0);
    nodesScrollLayout->setSpacing(20);
    nodesScrollLayout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    nodesScrollContainer->setLayout(nodesScrollLayout);

    parseNodeList();
}

void ProcessNodesContainer::resizeEvent(QResizeEvent *event) {
    nodesScrollArea->setFixedSize(size());
    nodesScrollContainer->setFixedWidth(width());
}

void ProcessNodesContainer::parseNodeList() {
    auto nodeWrapperMap = nodeManger.getNodes();
    auto nodeWrapperItem = nodeWrapperMap.cbegin();
    for(; nodeWrapperItem!=nodeWrapperMap.cend(); ++nodeWrapperItem) {
        auto node = createNodeFactory(nodeWrapperItem->second.getBaseNode());
        nodesScrollLayout->addWidget(node);
    }
}

QFrame* ProcessNodesContainer::createNodeFactory(const AbsNode &node) {
//  定义node GUI
    auto nodeContainer = new QFrame();
    //设置具体阴影
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 5);
    //阴影颜色
    shadow_effect->setColor(Qt::darkGray);
    //阴影半径
    shadow_effect->setBlurRadius(8);
    nodeContainer->setGraphicsEffect(shadow_effect);
    nodeContainer->setStyleSheet(
            "background-color:white;border: 1px solid lightgray;border-radius: 5px;"
    );
    nodeContainer->setFrameShape(QFrame::StyledPanel);
    nodeContainer->setFrameShadow(QFrame::Plain);
    nodeContainer->setFixedWidth(300);
    nodeContainer->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    auto nodeLayout = new QVBoxLayout();
    nodeLayout->setContentsMargins(10,10,10,10);
    nodeLayout->setSpacing(5);
    nodeLayout->setAlignment(Qt::AlignCenter);
    nodeContainer->setLayout(nodeLayout);

//  遍历control list，构建node
    auto controlList = node.getControls();
    auto nodeName = node.getDisplayName();
    auto control = controlList.begin();
    int nodeHeight = 0;
    int sH = 15; int mH = 33; int lH = 60;
    for(; control!=controlList.end(); ++control) {
//  根据control类型，添加子组件
        switch (control->getType()) {
            case SLIDER: {
                auto pSlider = new QSlider();
                auto sliderControl = control->getSliderControl();
                auto range = sliderControl.getRange();
                auto step = (range.second - range.first) / 20;
                pSlider->setFixedHeight(sH);
                pSlider->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
                pSlider->setOrientation(Qt::Horizontal);  // 水平方向
                pSlider->setRange(range.first, range.second);
                pSlider->setSingleStep(step); // 步长
                pSlider->setTickPosition(QSlider::TicksAbove);  //刻度在上方
                pSlider->setTracking(false);
                connect(pSlider, &QSlider::valueChanged, this,
                        [&sliderControl](int curValue) -> void {
                            sliderControl.setValue(curValue);
                            cout << sliderControl.getValue() << endl;
                        }
                );
                nodeLayout->addLayout(createControlLayout(
                        pSlider, QString::fromStdString(sliderControl.getDisplayName()), mH
                ));
                nodeHeight += sH;
                break;
            }
            case DIR_FIELD: {
                //  自定义widget，显示路径
                break;
            }
            case COMBO_BOX: {
                auto comboBox = new QComboBox();
                auto comboBoxControl = control->getComboBoxControl();
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
//                            to do 这里的control list有bug，运行时大小异常
//                            comboBoxControl.setSelected(curIndex);
                            cout << curIndex << endl;
                        }
                );
                nodeLayout->addLayout(createControlLayout(
                        comboBox, QString::fromStdString(comboBoxControl.getDisplayName()), mH
                ));
                nodeHeight += mH;
                break;
            }
            case BUTTON: {
                auto button = new QPushButton();
                auto buttonControl = control->getButtonControl();
                auto iconFilePath = getIconFilePath(buttonControl.getIconEnum());
                button->setStyleSheet("border: none;");
                button->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
                button->setIcon(QIcon(iconFilePath));
                connect(button, &QPushButton::clicked, this,
                        [&buttonControl]() -> void {
                           cout<< "click button" << endl;
                        }
                );
                nodeLayout->addWidget(button);
                nodeHeight += mH;
                break;
            }
            case CHECKBOX: {
                auto checkBox = new QCheckBox();
                auto checkBoxControl = control->getCheckboxControl();
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
                nodeLayout->addLayout(createControlLayout(
                        checkBox, QString::fromStdString(checkBoxControl.getDisplayName()), mH
                ));
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
                spinBox->setSingleStep(step);
                spinBox->setValue(spinBoxControl.getValue());
                connect(spinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
                        [&spinBoxControl](int curValue) -> void {
                            spinBoxControl.setValue(curValue);
                            cout<< curValue << endl;
                        }
                );
                nodeLayout->addLayout(createControlLayout(
                        spinBox, QString::fromStdString(spinBoxControl.getDisplayName()), mH
                ));
                nodeHeight += mH;
                break;
            }
            case SPIN_BOX_F: {
                auto spinBox = new QDoubleSpinBox();
                auto spinBoxControl = control->getSpinBoxControl<float>();
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
                nodeLayout->addLayout(createControlLayout(
                        spinBox, QString::fromStdString(spinBoxControl.getDisplayName()), mH
                ));
                nodeHeight += mH;
                break;
            }
            case COMPOSITE:
                break;
            default:
                break;
        }
    }

    nodeContainer->setFixedHeight(nodeHeight + nodeLayout->spacing() * (nodeLayout->count() - 1) + 20);
    nodesScrollContainer->setFixedHeight(nodesScrollContainer->height() + nodeContainer->height() + nodesScrollLayout->spacing());
    return nodeContainer;
}

QString ProcessNodesContainer::getIconFilePath(ICON icon) {
    switch (icon) {
        case IC_ADD: return QString::fromStdString("../UI_SRC/add.png");
        default:return QString::fromStdString("../UI_SRC/add.png");
    }
}

QHBoxLayout *ProcessNodesContainer::createControlLayout(QWidget *control, const QString& text, int height) {
    auto name = new QLabel();
    name->setStyleSheet("border: none;");
    name->setText(text);
    name->setFixedHeight(height);
    name->adjustSize();
    name->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    auto controlLayout = new QHBoxLayout();
    controlLayout->setContentsMargins(0,0,0,0);
    controlLayout->setSpacing(10);
    controlLayout->setAlignment(Qt::AlignCenter);
    controlLayout->addWidget(name);
    controlLayout->addWidget(control);
    return controlLayout;
}