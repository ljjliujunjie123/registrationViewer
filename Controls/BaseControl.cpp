//
// Created by ZZY on 2021/11/30.
//

#include "BaseControl.h"

const string &BaseControl::getDisplayName() const {
    return displayName;
}

BaseControl::BaseControl(const string &name, const string& desc) {
    displayName = name;
    description = desc;
}

const string &BaseControl::getDescription() const {
    return description;
}

void BaseControl::setDescription(const string& desc) {
    description = desc;
}



