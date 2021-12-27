//
// Created by ZZY on 2021/12/2.
//

#include "SliderControl.h"

void SliderControl::setRange(int min, int max) {
    if(max > min){
        range.first = min;
        range.second = max;
    }
}

const pair<int, int> &SliderControl::getRange() const {
    return range;
}

const int &SliderControl::getValue() const {
    return value;
}

void SliderControl::setValue(int val) {
    value = val;
}

void SliderControl::setValueChangedListener(function<void(int)> l) {
    onValueChangeListener = l;
}

SliderControl::SliderControl(int id, const string &name, const string &desc, pair<int, int> initRange, int defaultValue, bool enabled): BaseControl(id, name, desc, enabled){
    setRange(initRange.first, initRange.second);
    value = defaultValue;
    _type = SLIDER;
};





