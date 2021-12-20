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

class ProcessNodesContainer: public QFrame {

public:
    ProcessNodesContainer(QWidget *parent = nullptr);

protected:
    virtual void resizeEvent(QResizeEvent *event);

private:
    QScrollArea* nodesScrollArea;
    QFrame* nodesScrollContainer;
    QVBoxLayout* nodesScrollLayout;

    NodeManager* nodeManger;

    void parseNodeList();

    QFrame& createNodeFactory(AbsNode *node);
};


#endif //REGISTRATIONVIEWER_PROCESSNODESCONTAINER_H
