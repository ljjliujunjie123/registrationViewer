//
// Created by ZZY on 2021/11/30.
//

#ifndef REGISTRATIONVIEWER_COMPOSITECONTROL_H
#define REGISTRATIONVIEWER_COMPOSITECONTROL_H

#include "AbsControl.h"
#include "AbsSingleWidgetControl.h"
#include "../Utils/exceptions.cpp"
#include<list>
#include<optional>

class CompositeControl: public AbsControl {
public:
    list<AbsSingleWidgetControl>::const_iterator getSubControlList();
    void insertControl(AbsSingleWidgetControl control);
    const AbsSingleWidgetControl& findControlByName(const string& name);


private:
    list<AbsSingleWidgetControl> subControls;

};


#endif //REGISTRATIONVIEWER_COMPOSITECONTROL_H
