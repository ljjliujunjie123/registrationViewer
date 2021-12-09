//
// Created by ZZY on 2021/12/2.
//

#ifndef REGISTRATIONVIEWER_SPINBOXCONTROL_H
#define REGISTRATIONVIEWER_SPINBOXCONTROL_H
#include "AbsSingleWidgetControl.h"
#include<utility>

template<typename T>
class SpinBoxControl: public AbsSingleWidgetControl{
public:
    void setRange(T min, T max);
    const pair<T, T>& getRange() const;

    void setValue(T val);
    const T& getValue() const;

private:
    pair<T, T> range = make_pair(0.0,1.0);
    int value = range.first;
};




#endif //REGISTRATIONVIEWER_SPINBOXCONTROL_H
