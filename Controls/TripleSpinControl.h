//
// Created by ZZY on 2021/12/27.
//

#ifndef REGISTRATIONVIEWER_TRIPLESPINCONTROL_H
#define REGISTRATIONVIEWER_TRIPLESPINCONTROL_H
#include "BaseControl.h"
#include<utility>

class TripleSpinControl: public BaseControl {
public:
    enum SPIN_POS {ONE, TWO, THREE};
    struct SpinDescriptor{
        int minValue;
        int maxValue;
        int value;
        string name;
    };
    TripleSpinControl(int id, string name, string desc, SpinDescriptor item1, SpinDescriptor item2, SpinDescriptor item3, bool enabled = true);
    void setValueOf(SPIN_POS pos, int value);
    SpinDescriptor& getSpinOf(SPIN_POS pos) ;

private:
    SpinDescriptor spin1;
    SpinDescriptor spin2;
    SpinDescriptor spin3;
};


#endif //REGISTRATIONVIEWER_TRIPLESPINCONTROL_H
