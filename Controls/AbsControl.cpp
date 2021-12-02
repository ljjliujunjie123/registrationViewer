//
// Created by ZZY on 2021/11/30.
//
#include "AbsControl.h"

const string &AbsControl::getDisplayName() const {
    return displayName;
}

AbsControl::AbsControl(const string &name) {
    displayName = name;
}
