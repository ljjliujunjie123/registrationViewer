//
// Created by ZZY on 2021/11/30.
//
#include "AbsControl.h"

#include <utility>

const string &AbsControl::getDisplayName() const {
    return displayName;
}

AbsControl::AbsControl(const string &name) {
    displayName = name;
}

const string &AbsControl::getDescription() const {
    return description;
}

void AbsControl::setDescription(const string& desc) {
    description = desc;
}
