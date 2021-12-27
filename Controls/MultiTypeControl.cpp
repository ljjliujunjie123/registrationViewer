//
// Created by ZZY on 2021/12/27.
//

#include "MultiTypeControl.h"

MultiTypeControl::MultiTypeControl(int id, string name, string desc, map<string, list<SingleControlWrapper>> controlMap,
                                   string defaultSelected, bool enabled): BaseControl(id, name, desc, enabled) {
    selected = defaultSelected;
    subControlMap = controlMap;
}

const map<string, list<SingleControlWrapper>> &MultiTypeControl::getSubControlMap() const {
    return subControlMap;
}

void MultiTypeControl::setSelected(string option) {
    selected = option;
}

const string &MultiTypeControl::getSelected() const {
    return selected;
}
