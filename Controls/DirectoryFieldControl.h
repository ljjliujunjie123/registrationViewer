//
// Created by ZZY on 2021/12/9.
//

#ifndef REGISTRATIONVIEWER_DIRECTORYFIELDCONTROL_H
#define REGISTRATIONVIEWER_DIRECTORYFIELDCONTROL_H
#include "BaseControl.h"

class DirectoryFieldControl: public BaseControl {
public:
    DirectoryFieldControl(int id, const string &name, const string& desc, bool enabled = true): BaseControl(id, name, desc, enabled){
        _type = DIR_FIELD;
    };
    const string& getDir() const;
    void setDir(string dir);
    void setValueChangedListener(function<void(string)> l );


private:
    string dir = "";
    function<void(string)> onValueChangeListener;
};


#endif //REGISTRATIONVIEWER_DIRECTORYFIELDCONTROL_H
