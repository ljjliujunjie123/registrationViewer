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
    auto nodeWrapperList = nodeManger.getNodes();
    auto nodeWrapper = nodeWrapperList.begin();
    for(; nodeWrapper!=nodeWrapperList.end(); ++nodeWrapper) {
        nodeWrapper->getDisplayName();
        auto node = createNodeFactory(nodeWrapper->getNode());
        nodesScrollLayout->addWidget(node);
    }
}

QFrame* ProcessNodesContainer::createNodeFactory(AbsNode *node) {
//  定义node GUI
    auto nodeContainer = new QFrame();
//    nodeContainer->setStyleSheet("background-color:#fce1df;");
    nodeContainer->setFrameShape(QFrame::StyledPanel);
    nodeContainer->setFrameShadow(QFrame::Plain);
    nodeContainer->setFixedWidth(300);
    nodeContainer->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    auto nodeLayout = new QVBoxLayout();
    nodeLayout->setContentsMargins(0,0,0,0);
    nodeLayout->setSpacing(5);
    nodeLayout->setAlignment(Qt::AlignCenter);
    nodeContainer->setLayout(nodeLayout);

//  遍历control list，构建node
    auto controlList = node->getControls();
    auto nodeName = node->getDisplayName();
    auto control = controlList.begin();
    int nodeHeight = 0;
    int sH = 15; int mH = 35; int lH = 60;
    for(; control!=controlList.end(); ++control) {
//  根据control类型，添加子组件
        switch (control->getType()) {
            case SLIDER: {
                auto pSlider = new QSlider();
                auto sliderControl = control->getSliderControl();
                auto range = sliderControl.getRange();
                auto step = (range.second - range.first) / 20;
                pSlider->setFixedHeight(sH);
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
                nodeLayout->addWidget(pSlider);
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
                comboBox->addItem(QString("heloow"), "");
                comboBox->addItem(QString("heloow"), "");
                comboBox->setFixedHeight(mH);
                comboBox->setCurrentIndex(0);
                connect(comboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,
                        [&comboBoxControl](int curIndex) -> void {
//                            to do 这里的control list有bug，运行时大小异常
//                            comboBoxControl.setSelected(curIndex);
                            cout << curIndex << endl;
                        }
                );
                nodeLayout->addWidget(comboBox);
                nodeHeight += mH;
                break;
            }
            case BUTTON: {
                auto button = new QPushButton();
                auto buttonControl = control->getButtonControl();
                auto iconFilePath = getIconFilePath(buttonControl.getIconEnum());
                button->setIconSize(QSize(32,32));
                button->setIcon(QIcon(iconFilePath));
                connect(button, &QPushButton::clicked, this,
                        [&buttonControl]() -> void {
                           cout<< "click button" << endl;
                        }
                );
                nodeLayout->addWidget(button);
                nodeHeight += 40;
                break;
            }
            case CHECKBOX: {
                auto checkBox = new QCheckBox();
                auto checkBoxControl = control->getCheckboxControl();
                auto text = QString::fromStdString(checkBoxControl.getDisplayName());
                checkBox->setFixedHeight(mH);
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
                nodeLayout->addWidget(checkBox);
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
                spinBox->setRange(range.first, range.second);
                spinBox->setSingleStep(step);
                spinBox->setValue(spinBoxControl.getValue());
                connect(spinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
                        [&spinBoxControl](int curValue) -> void {
                            spinBoxControl.setValue(curValue);
                            cout<< curValue << endl;
                        }
                );
                nodeLayout->addWidget(spinBox);
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
                spinBox->setRange(range.first, range.second);
                spinBox->setSingleStep(step);
                spinBox->setValue(spinBoxControl.getValue());
                connect(spinBox, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this,
                        [&spinBoxControl](double curValue) -> void {
                            spinBoxControl.setValue((float)curValue);
                            cout<< curValue << endl;
                        }
                );
                nodeLayout->addWidget(spinBox);
                nodeHeight += mH;
                break;
            }
            case COMPOSITE:
                break;
            default:
                break;
        }
    }

    nodeContainer->setFixedHeight(nodeHeight + nodeLayout->spacing() * (nodeLayout->count() - 1));
    nodesScrollContainer->setFixedHeight(nodesScrollContainer->height() + nodeContainer->height() + nodesScrollLayout->spacing());
    return nodeContainer;
}

QString ProcessNodesContainer::getIconFilePath(ICON icon) {
    switch (icon) {
        case IC_ADD: return QString::fromStdString("../UI_SRC/add.png");
        default:return QString::fromStdString("../UI_SRC/add.png");
    }
}
