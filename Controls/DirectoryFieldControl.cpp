//
// Created by ZZY on 2021/12/9.
//

#include "DirectoryFieldControl.h"

const string &DirectoryFieldControl::getDir() const {
    return dir;
}

void DirectoryFieldControl::setDir(string d) {
    dir = d;
}

void DirectoryFieldControl::setValueChangedListener(function<void(string)> l) {
    onValueChangeListener = l;
}
