#include "mainwindow.h"
#include <QApplication>
#include<iostream>
#include<string>
#include <QFile>
#include "test.cpp"
#include "Nodes/NodeManager.h"

using namespace std;

int hello(){
    std::cout<<"Hello"<<std::endl;
}

void initNodeManager(){
    NodeManager& inst = NodeManager::getInstance();
    inst.registerNode(NodeWrapper(TestNode("test node", "test node desc")), "TestNode in List");
    inst.registerNode(NodeWrapper(AntsRigidRegistrationNode("Ants Registration Rigid", "")), "Ants Registration Rigid");
    inst.registerNode(NodeWrapper(AntsAffineRegistrationNode("ants_affine", "")), "Ants Registration Affine");
    inst.registerNode(NodeWrapper(AntsSyNRegistrationNode("ants_syn", "")), "Ants Deformable Registration SyN");
    //    auto it = inst.getNodes().cbegin();
//    while (it != inst.getNodes().cend()){
//        cout<<it->first<<" "<<it->second.getDisplayName()<<endl;
//    }
}

int main(int argc, char *argv[])
{
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());
    testEntry();
    initNodeManager();
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    QFile qssFile("myQSS.qss");
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        QString qss = QLatin1String(qssFile.readAll());
        qApp->setStyleSheet(qss);
        qssFile.close();
    }
    MainWindow w;
    w.show();
    return a.exec();
}