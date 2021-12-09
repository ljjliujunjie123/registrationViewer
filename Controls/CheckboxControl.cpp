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

void CheckboxControl::setValueChangedListener(function<void(bool)> l) {
    onValueChangeListener = l;
}

CheckboxControl::CheckboxControl(const string &name, const string &desc, bool isChecked): BaseControl(name, desc){
    _checked = isChecked;
    _type = CHECKBOX;
}



