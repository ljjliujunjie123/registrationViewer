//
// Created by ZZY on 2021/12/9.
//

#include<list>
//#include "AbsSingleWidgetControl.h"
#include "ControlWrapper.h"
#include<iostream>


void test();

int main(){
    test();
    return 0;
}

void test(){
    list<ControlWrapper> l;
    ComboBoxControl entry("Combo Test", "", {"hello"}, "world");
    ControlWrapper w(entry);
    l.push_back(w);
    auto it = l.begin();
    switch (it->getType()) {
        case COMBO_BOX: {
            cout<<it->getComboBoxControl().getDefaultOption()<<endl;
        }
        default: return;
    }
    return;
}