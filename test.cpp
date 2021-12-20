//
// Created by ZZY on 2021/12/16.
//
#ifndef TOPLEVEL_TEST_CPP
#define TOPLEVEL_TEST_CPP

#include "vtkLogoWidget.h"
#include<iostream>
#include<string>

#include "Controls/SpinBoxControl.h"

using namespace std;


inline void testVtkInteract(){
    vtkLogoWidget* widget;
    cout<<"pass"<<endl;
}

inline void testControlTemplate(){
    SpinBoxControl<int> control(1, "Hello", "", {9,10});
    if( control.getValue() == 9 ) cout<<"pass"<<endl;
    else cout<<"failed"<<endl;
}

inline void testEntry(){
    cout<<"Testing..."<<endl;
    cout<<"Testing vtkInteract...";
    testVtkInteract();
    cout<<"Testing ControlTemplate...";
    testControlTemplate();
}

#endif // TOPLEVEL_TEST_CPP

