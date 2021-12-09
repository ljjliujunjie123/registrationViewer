//
// Created by ZZY on 2021/12/2.
//

#ifndef REGISTRATIONVIEWER_CHECKBOXCONTROL_H
#define REGISTRATIONVIEWER_CHECKBOXCONTROL_H
#include "BaseControl.h"

class CheckboxControl: public BaseControl {
public:
    CheckboxControl(const string &name, const string &desc, bool isChecked);
    bool isChecked() const;
    void setChecked(bool checked);
    void setValueChangedListener(function<void(bool)> l );

private:
    bool _checked = false;
    function<void(bool)> onValueChangeListener;

};


#endif //REGISTRATIONVIEWER_CHECKBOXCONTROL_H
