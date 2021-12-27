//
// Created by ZZY on 2021/12/2.
//

#ifndef REGISTRATIONVIEWER_SLIDERCONTROL_H
#define REGISTRATIONVIEWER_SLIDERCONTROL_H
#include "BaseControl.h"
#include<utility>

using namespace std;


class SliderControl: public BaseControl {
public:
    SliderControl(int id, const string &name, const string &desc, pair<int, int> initRange, int defaultValue, bool enabled = true);
    void setRange(int min, int max);
    const pair<int, int>& getRange() const;

    void setValue(int val);
    const int& getValue() const;

    void setValueChangedListener(function<void(int)> l );


private:
    pair<int, int> range = make_pair(0.0,1.0);
    int value = range.first;
    function<void(int)> onValueChangeListener;
};


#endif //REGISTRATIONVIEWER_SLIDERCONTROL_H
