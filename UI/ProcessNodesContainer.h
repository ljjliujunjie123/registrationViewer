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
#include "qprogressbar.h"
#include "NPushButtonExtend.h"
#include "../Nodes/NodeManager.h"
#include "../Nodes/NodeWrapper.h"
#include "../Nodes/AbsNode.h"
#include "../Controls/BaseControl.h"
#include "../Controls/ButtonControl.h"
#include "../Controls/TripleSpinControl.h"
#include <QSlider>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QCheckBox>
#include <QGraphicsDropShadowEffect>
#include <QColor>

class ProcessNodesContainer: public QFrame {
Q_OBJECT
public:
    ProcessNodesContainer(QWidget *parent = nullptr);

    const string& getSaveDir() const {
        return saveDir;
    };

Q_SIGNALS:
    void startSignal();

protected:
    virtual void resizeEvent(QResizeEvent *event);
private:
    QScrollArea* nodesScrollArea;
    QFrame* nodesScrollContainer;
    NPushButtonExtend* nodeMenuButton;
    QVBoxLayout* nodesScrollLayout;
    QHBoxLayout* nodesMenuLayout;
    QPushButton* startButton;
    NodeManager& nodeManger = NodeManager::getInstance();

    string saveDir = "";

    void parseNodeMenu();

    QString getIconFilePath(ICON icon);

    QFrame* createNodeFactory(const AbsNode& node);

    QFrame* createCompositeControl(const CompositeControl& compositeControl);

    QFrame* createMultiControl(MultiTypeControl& multiTypeControl, QFrame& nodeContainer);

    QLabel* createControlName(const QString& text, int height, bool isBold = false, int width = 220);

    QHBoxLayout* createNodeTitle(QFrame& nodeContainer, const QString& text, int height);

    QVBoxLayout* createNodeTail(AbsNode node, int height);

    QHBoxLayout* createSaveDir(int height);

    QHBoxLayout* createStartLayout(int height);

    QVBoxLayout* createSingleTripple(TripleSpinControl::SpinDescriptor& mstruct, int height);

    QFrame* createMultiControlList(list<SingleControlWrapper>& controlList);
};

#endif //REGISTRATIONVIEWER_PROCESSNODESCONTAINER_H
