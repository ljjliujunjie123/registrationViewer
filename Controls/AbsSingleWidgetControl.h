//
// Created by ZZY on 2021/11/30.
//

#ifndef REGISTRATIONVIEWER_ABSSINGLEWIDGETCONTROL_H
#define REGISTRATIONVIEWER_ABSSINGLEWIDGETCONTROL_H

#include "AbsControl.h"

enum CONTROL_WIDGETS{SLIDER, TEXT_FIELD, DROP_DOWN, BUTTON, CHECKBOX, ADD_BUTTON};
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
