//
// Created by ZZY on 2021/11/30.
//

#ifndef REGISTRATIONVIEWER_COMPOSITECONTROL_H
#define REGISTRATIONVIEWER_COMPOSITECONTROL_H

#include "BaseControl.h"
#include "BaseControl.h"
#include "../Utils/exceptions.cpp"
#include<list>
#include<optional>

class CompositeControl: public BaseControl {
public:
    CompositeControl(const string& name, const string& desc, list<BaseControl> initialList);
    const list<BaseControl>& getSubControlList();
    void insertControl(BaseControl control);
    const BaseControl& findControlByName(const string& name);


private:
    list<BaseControl> subControls;

};


#endif //REGISTRATIONVIEWER_COMPOSITECONTROL_H
