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
//    ComboBoxControl entry("Combo Test", "", {"hello"}, "world");
    auto cmp =  CompositeControl(2,"hsd", "ds",
                                 {
                                         SingleControlWrapper(ComboBoxControl(3, "Combo Test", "", {"hello"}, "world")),
                                         SingleControlWrapper(ButtonControl(4, "Button Test", "World", IC_HOME, true))
                                 });
    ControlWrapper wc(cmp);
    l.push_back(wc);
    l.emplace_back(ControlWrapper(ButtonControl(1, "Hello", "World", IC_SEARCH, true)));
//    SingleControlWrapper sw(ButtonControl(1, "Hello", "World", IC_MINUS, true));
    auto it = l.begin();
    it++;
    switch (it->getType()) {
        case COMBO_BOX: {
            cout<<it->getComboBoxControl().getDefaultOption()<<endl;
            break;
        }
        case BUTTON:
            cout<<it->getButtonControl().getIconEnum()<<endl;
            break;
        case COMPOSITE:{
            auto c = it->getCompositeControl();
            for ( auto it = c.getSubControlList().cbegin(); it != c.getSubControlList().cend(); it++){
                cout<<it->getType()<<it->getDisplayName()<<endl;
            }
            break;
        }
        default: return;
    }
    return;
}