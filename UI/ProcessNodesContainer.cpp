//
// Created by 19956875375 on 2021/12/15.
//

#include "ProcessNodesContainer.h"

ProcessNodesContainer::ProcessNodesContainer(QWidget *parent) {
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Plain);

    nodesScrollArea = new QScrollArea(this);
    nodesScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    nodesScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    nodesScrollArea->setFixedSize(size());

    nodesScrollContainer = new QFrame(nodesScrollArea);
    nodesScrollContainer->setFixedSize(size());
    nodesScrollArea->setWidget(nodesScrollContainer);

    nodesScrollLayout = new QVBoxLayout();
    nodesScrollLayout->setContentsMargins(0,0,0,0);
    nodesScrollLayout->setSpacing(5);
    nodesScrollLayout->setAlignment(Qt::AlignHCenter);
    nodesScrollContainer->setLayout(nodesScrollLayout);

}

void ProcessNodesContainer::resizeEvent(QResizeEvent *event) {
    nodesScrollArea->setFixedSize(size());
    nodesScrollContainer->setFixedSize(size());
}

void ProcessNodesContainer::parseNodeList() {
    auto nodeWrapperList = nodeManger->getNodes();
    auto nodeWrapper = nodeWrapperList.begin();
    for(; nodeWrapper!=nodeWrapperList.end(); ++nodeWrapper) {
        nodeWrapper->getDisplayName();
//        nodesScrollLayout->addWidget(createNodeFactory(nodeWrapper.getNode()))
    }
}

QFrame& ProcessNodesContainer::createNodeFactory(AbsNode *node) {
//  定义node GUI
    auto nodeContainer = new QFrame();
    nodeContainer->setFrameShape(QFrame::StyledPanel);
    nodeContainer->setFrameShadow(QFrame::Plain);
    nodeContainer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    auto nodeLayout = new QVBoxLayout();
    nodeLayout->setContentsMargins(0,0,0,0);
    nodeLayout->setAlignment(Qt::AlignCenter);
    nodeContainer->setLayout(nodeLayout);

//  遍历control list，构建node
    auto controlList = node->getControls();
    auto nodeName = node->getDisplayName();
    auto control = controlList.begin();
    int nodeHeight = 0;
    for(; control!=controlList.end(); ++control) {
        node += 30;
    }

    nodeContainer->setFixedHeight(nodeHeight);
    return *nodeContainer;
}
