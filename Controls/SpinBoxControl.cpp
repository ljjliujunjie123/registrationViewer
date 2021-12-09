//
// Created by ZZY on 2021/12/2.
//

#include "SpinBoxControl.h"

template<typename T>
void SpinBoxControl<T>::setRange(T min, T max) {
    if(max > min){
        range.first = min;
        range.second = max;
    }
}

template<typename T>
const pair<T, T> &SpinBoxControl<T>::getRange() const {
    return range;
}

template<typename T>
const T &SpinBoxControl<T>::getValue() const {
    return value;
}

template<typename T>
void SpinBoxControl<T>::setValue(T val) {
    value = val;
}

template<typename numberType>
void SpinBoxControl<numberType>::setValueChangedListener(function<void(numberType)> l) {
    onValueChangeListener = l;
}

template<typename numberType>
SpinBoxControl<numberType>::SpinBoxControl(const string &name, const string &desc, pair<numberType, numberType> initRange): BaseControl(name, desc) {
    range = initRange;
    value = initRange.first;
    if(is_same<numberType, int>::value) _type = SPIN_BOX_I;
    else if(is_same<numberType, float>::value) _type = SPIN_BOX_F;
}



