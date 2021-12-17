//
// Created by ZZY on 2021/11/30.
//

#include "CompositeControl.h"


void CompositeControl::insertControl(SingleControlWrapper& control) {
    subControls.insert(subControls.end(), control);
}

const SingleControlWrapper& CompositeControl::findControlByName(const string &name) {
    auto it = subControls.cbegin();
    while(it!=subControls.cend()){
        if (it->getDisplayName() == name) return *it;
        it++;
    }
    throw NotFoundException();
}

const list<SingleControlWrapper> & CompositeControl::getSubControlList() const {
    return subControls;
}

CompositeControl::CompositeControl(int id, const string &name, const string &desc, list<SingleControlWrapper> initialList, bool enabled): BaseControl(id, name, desc, enabled) {
    subControls = initialList;
    _type = COMPOSITE;
}


