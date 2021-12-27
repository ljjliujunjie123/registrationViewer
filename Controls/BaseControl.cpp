//
// Created by ZZY on 2021/11/30.
//

#include "BaseControl.h"

const string &BaseControl::getDisplayName() const {
    return displayName;
}

BaseControl::BaseControl(int id, string name, string desc, bool enabled) {
    _id = id;
    displayName = name;
    description = desc;
     _enabled = enabled;
}

const string &BaseControl::getDescription() const {
    return description;
}

void BaseControl::setDescription(const string& desc) {
    description = desc;
}



