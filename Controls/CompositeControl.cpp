//
// Created by ZZY on 2021/11/30.
//

#include "CompositeControl.h"

list<AbsSingleWidgetControl>::const_iterator CompositeControl::getSubControlList() {
    return subControls.cbegin();
}

void CompositeControl::insertControl(AbsSingleWidgetControl control) {
    subControls.insert(subControls.end(), control);
}

const AbsSingleWidgetControl& CompositeControl::findControlByName(const string &name) {
    auto it = subControls.cbegin();
    while(it!=subControls.cend()){
        if (it->getDisplayName() == name) return *it;
        it++;
    }
    throw NotFoundException();
}
