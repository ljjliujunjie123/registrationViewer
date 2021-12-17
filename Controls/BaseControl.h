//
// Created by ZZY on 2021/11/30.
//

#ifndef REGISTRATIONVIEWER_BASECONTROL_H
#define REGISTRATIONVIEWER_BASECONTROL_H

#include<string>
#include<functional>
#include<iostream>
#include "../Utils/exceptions.h"

using namespace std;

enum CONTROL_TYPE{SLIDER, DIR_FIELD, COMBO_BOX, BUTTON, CHECKBOX, SPIN_BOX_I, SPIN_BOX_F, COMPOSITE, ABSTRACT};
class BaseControl{
public:
    BaseControl();
    BaseControl(int id, const string& name, const string& desc, bool enabled = true);
    virtual CONTROL_TYPE getControlType() const{
         return _type;
    };

    const string& getDisplayName() const;
    void setEnabled(bool enabled){
        _enabled = enabled;
    }
    const string& getDescription() const;
    void setDescription(const string& desc);
    int getId() const{
        return _id;
    }

protected:
    int _id = 0;
    bool _enabled = true;
    string displayName;
    string description;
    CONTROL_TYPE _type;
};


#endif //REGISTRATIONVIEWER_BASECONTROL_H
