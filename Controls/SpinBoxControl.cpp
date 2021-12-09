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

