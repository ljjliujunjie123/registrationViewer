//
// Created by ZZY on 2021/11/30.
//

#ifndef REGISTRATIONVIEWER_BASECONTROL_H
#define REGISTRATIONVIEWER_BASECONTROL_H

#include<string>

using namespace std;

enum CONTROL_TYPE{SLIDER, DIR_FIELD, COMBO_BOX, BUTTON, CHECKBOX, SPIN_BOX, COMPOSITE, ABSTRACT};
class BaseControl{
public:
    BaseControl();
    BaseControl(const string& name, const string& desc);
    virtual CONTROL_TYPE getControlType() const{
         return _type;
    };

    const string& getDisplayName() const;
    void setEnabled(bool enabled){
        _enabled = enabled;
    }
    const string& getDescription() const;
    void setDescription(const string& desc);

protected:
    bool _enabled = true;
    string displayName;
    string description;
    CONTROL_TYPE _type;
};


#endif //REGISTRATIONVIEWER_BASECONTROL_H
