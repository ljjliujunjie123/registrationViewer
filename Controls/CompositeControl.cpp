//
// Created by ZZY on 2021/11/30.
//

#include "CompositeControl.h"


void CompositeControl::insertControl(BaseControl control) {
    subControls.insert(subControls.end(), control);
}

const BaseControl& CompositeControl::findControlByName(const string &name) {
    auto it = subControls.cbegin();
    while(it!=subControls.cend()){
        if (it->getDisplayName() == name) return *it;
        it++;
    }
    throw NotFoundException();
}

const list<BaseControl>& CompositeControl::getSubControlList() {
    return subControls;
}

CompositeControl::CompositeControl(const string &name, const string &desc, list<BaseControl> initialList): BaseControl(name, desc) {
    subControls = move(initialList);
    _type = COMPOSITE;
}

