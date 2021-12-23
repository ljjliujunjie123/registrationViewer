//
// Created by 19956875375 on 2021/12/15.
//

#ifndef REGISTRATIONVIEWER_PROCESSNODESCONTAINER_H
#define REGISTRATIONVIEWER_PROCESSNODESCONTAINER_H

#include <QFrame>
#include "qfiledialog.h"
#include "qlineedit.h"
#include "qboxlayout.h"
#include "qformlayout.h"
#include "qscrollarea.h"
#include "NPushButtonExtend.h"
#include "../Nodes/NodeManager.h"
#include "../Nodes/NodeWrapper.h"
#include "../Nodes/AbsNode.h"
#include "../Controls/BaseControl.h"
#include "../Controls/ButtonControl.h"
#include <QSlider>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QCheckBox>
#include <QGraphicsDropShadowEffect>
#include <QColor>

class ProcessNodesContainer: public QFrame {

public:
    ProcessNodesContainer(QWidget *parent = nullptr);

protected:
    virtual void resizeEvent(QResizeEvent *event);
private:
    QScrollArea* nodesScrollArea;
    QFrame* nodesScrollContainer;
    NPushButtonExtend* nodeMenuButton;
    QVBoxLayout* nodesScrollLayout;
    QHBoxLayout* nodesMenuLayout;

    NodeManager& nodeManger = NodeManager::getInstance();

    void parseNodeMenu();

    QString getIconFilePath(ICON icon);

    QFrame* createNodeFactory(const AbsNode& node);

    QFrame* createCompositeControl(const CompositeControl& compositeControl);

    QLabel* createControlName(const QString& text, int height, int width = 150);
};

#endif //REGISTRATIONVIEWER_PROCESSNODESCONTAINER_H
