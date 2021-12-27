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
    SpinBoxControl(int id, const string& name, const string& desc,pair<numberType, numberType> initRange, numberType defaultValue, bool enabled = true): BaseControl(id, name, desc, enabled) {
        range = initRange;
        value = defaultValue;
        if(is_same<numberType, int>::value) _type = SPIN_BOX_I;
        else if(is_same<numberType, float>::value) _type = SPIN_BOX_F;
    }

    void setRange(numberType min, numberType max) {
        if(max > min){
            range.first = min;
            range.second = max;
        }
    }

    const pair<numberType, numberType>& getRange() const {
        return range;
    }

    void setValue(numberType val) {
        value = val;
    }

    numberType getValue() const {
        return value;
    }

    void setValueChangedListener(function<void(numberType)> l) {
        onValueChangeListener = l;
    }


private:
    pair<numberType, numberType> range = make_pair(0.0, 1.0);
    function<void(numberType)> onValueChangeListener;
    numberType value = range.first;
};



#endif //REGISTRATIONVIEWER_SPINBOXCONTROL_H
