//
// Created by ZZY on 2021/12/9.
//

#include "ButtonControl.h"

void ButtonControl::setOnClickListener(function<void(void)> l) {
    onClickListener = l;
}

const ICON ButtonControl::getIconEnum() const {
    return icon;
}

const bool ButtonControl::isShowLabel() const {
    return labelShow;
}

