#include "mainwindow.h"

#include <QApplication>
#include<iostream>
#include<string>
#include "test.cpp"
#include "Nodes/NodeManager.h"


using namespace std;


int main(int argc, char *argv[])
{
    testEntry();
    initNodeManager();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

int hello(){
    std::cout<<"Hello"<<std::endl;
}


