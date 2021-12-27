//
// Created by ZZY on 2021/12/27.
//

#include "TripleSpinControl.h"


TripleSpinControl::TripleSpinControl(int id, string name, string desc, TripleSpinControl::SpinDescriptor item1,
                                     TripleSpinControl::SpinDescriptor item2, TripleSpinControl::SpinDescriptor item3,
                                     bool enabled): BaseControl(id, name, desc, enabled) {
    spin1 = item1;
    spin2 = item2;
    spin3 = item3;
}

void TripleSpinControl::setValueOf(TripleSpinControl::SPIN_POS pos, int value) {
    switch (pos) {
        case ONE: spin1.value = value; return;
        case TWO: spin2.value = value; return;
        case THREE: spin3.value = value; return;
        default: return;
    }
}

TripleSpinControl::SpinDescriptor &TripleSpinControl::getSpinOf(TripleSpinControl::SPIN_POS pos)  {
    switch(pos){
        case ONE: return spin1;
        case TWO: return spin2;
        case THREE: return spin3;
    }
}
