//
// Created by ZZY on 2021/11/30.
//

#ifndef REGISTRATIONVIEWER_ABSSINGLEWIDGETCONTROL_H
#define REGISTRATIONVIEWER_ABSSINGLEWIDGETCONTROL_H

#include "AbsControl.h"

enum CONTROL_WIDGETS{SLIDER, TEXT_FIELD, COMBO_BOX, BUTTON, CHECKBOX, ADD_BUTTON, SBIN_BOX};
class AbsSingleWidgetControl: public AbsControl {
public:
    const CONTROL_WIDGETS& getControlType() const
    {
        return _type;
    }

protected:
    CONTROL_WIDGETS _type;
};


#endif //REGISTRATIONVIEWER_ABSSINGLEWIDGETCONTROL_H
