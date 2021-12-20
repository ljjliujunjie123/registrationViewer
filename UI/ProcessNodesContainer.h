//
// Created by 19956875375 on 2021/12/15.
//

#ifndef REGISTRATIONVIEWER_PROCESSNODESCONTAINER_H
#define REGISTRATIONVIEWER_PROCESSNODESCONTAINER_H

#include <QFrame>
#include "qboxlayout.h"
#include "qscrollarea.h"
#include "../Nodes/NodeManager.h"
#include "../Nodes/NodeWrapper.h"
#include "../Nodes/AbsNode.h"
#include "../Controls/BaseControl.h"
#include "../Controls/ButtonControl.h"
#include <QSlider>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QCheckBox>

class ProcessNodesContainer: public QFrame {

public:
    ProcessNodesContainer(QWidget *parent = nullptr);

protected:
    virtual void resizeEvent(QResizeEvent *event);
private:
    QScrollArea* nodesScrollArea;
    QFrame* nodesScrollContainer;
    QHBoxLayout* spacerHLayout;
    QVBoxLayout* nodesScrollLayout;

    NodeManager& nodeManger = NodeManager::getInstance();

    void parseNodeList();

    QString getIconFilePath(ICON icon);

    QFrame* createNodeFactory(AbsNode *node);
};


#endif //REGISTRATIONVIEWER_PROCESSNODESCONTAINER_H
