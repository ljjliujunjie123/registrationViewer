#include "mainwindow.h"

#include <QApplication>
#include<iostream>
#include<string>

#include "test.cpp"


using namespace std;


int main(int argc, char *argv[])
{
    testEntry();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

int hello(){
    std::cout<<"Hello"<<std::endl;
}


