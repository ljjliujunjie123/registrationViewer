//
// Created by ZZY on 2021/12/2.
//

#ifndef REGISTRATIONVIEWER_SPINBOXCONTROL_H
#define REGISTRATIONVIEWER_SPINBOXCONTROL_H
#include "BaseControl.h"
#include<utility>

template<typename numberType>
class SpinBoxControl: public BaseControl{
public:
    SpinBoxControl(const string& name, const string& desc,pair<numberType, numberType> initRange);
    void setRange(numberType min, numberType max);
    const pair<numberType, numberType>& getRange() const;

    void setValue(numberType val);
    const numberType& getValue() const;
    void setValueChangedListener(function<void(numberType)> l );


private:
    pair<numberType, numberType> range = make_pair(0.0, 1.0);
    function<void(numberType)> onValueChangeListener;
    int value = range.first;
};




#endif //REGISTRATIONVIEWER_SPINBOXCONTROL_H
