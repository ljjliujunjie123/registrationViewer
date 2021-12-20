//
// Created by ZZY on 2021/12/9.
//

#ifndef REGISTRATIONVIEWER_BUTTONCONTROL_H
#define REGISTRATIONVIEWER_BUTTONCONTROL_H

#include "BaseControl.h"

enum ICON {
    IC_ADD, IC_MINUS, IC_ME, IC_HOME, IC_CLOSE, IC_SEARCH
};

class ButtonControl : public BaseControl {
public:
    ButtonControl(int id, const string &name, const string &desc, ICON ic, bool showLabel, bool enabled = true) : BaseControl(id, name, desc, enabled),
                                                                                     icon(ic),
                                                                                     labelShow(showLabel) {
        _type = BUTTON;
    };

    void setOnClickListener(function<void(void)> l );
    const ICON getIconEnum() const ;
    const bool isShowLabel() const ;


private:
    ICON icon;
    bool labelShow;
    function<void(void)> onClickListener;
};


#endif //REGISTRATIONVIEWER_BUTTONCONTROL_H
