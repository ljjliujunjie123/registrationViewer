//
// Created by ZZY on 2021/12/2.
//

#ifndef REGISTRATIONVIEWER_SLIDERCONTROL_H
#define REGISTRATIONVIEWER_SLIDERCONTROL_H
#include "AbsSingleWidgetControl.h"
#include<utility>

using namespace std;


class SliderControl: public AbsSingleWidgetControl {
public:
    void setRange(int min, int max);
    const pair<int, int>& getRange() const;

    void setValue(int val);
    const int& getValue() const;

private:
    pair<int, int> range = make_pair(0.0,1.0);
    int value = range.first;
};


#endif //REGISTRATIONVIEWER_SLIDERCONTROL_H
