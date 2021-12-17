//
// Created by ZZY on 2021/12/2.
//

#include "ComboBoxControl.h"

const vector<string>& ComboBoxControl::getOptionList() const {
    return optionList;
}

const string &ComboBoxControl::getDefaultOption() const {
    return defaultOption;
}

void ComboBoxControl::setSelected(int index) {
    currentSelected = optionList[index];
}

ComboBoxControl::ComboBoxControl(int id, const string &name, const string &desc, vector<string>&& options, const string& defaultOpt, bool enabled): BaseControl(id, name, desc, enabled) {
    optionList = options;
    defaultOption = defaultOpt;
    currentSelected = defaultOpt;
    _type = COMBO_BOX;
}

void ComboBoxControl::setValueChangedListener(function<void(string)> l) {
    onValueChangeListener = l;
}

const string &ComboBoxControl::getSelected() const {
    return currentSelected;
}





