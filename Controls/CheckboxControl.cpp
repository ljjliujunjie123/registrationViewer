//
// Created by ZZY on 2021/12/2.
//

#include "CheckboxControl.h"

bool CheckboxControl::isChecked() const {
    return _checked;
}

void CheckboxControl::setChecked(bool checked) {
    _checked = checked;
}
