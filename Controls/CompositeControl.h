//
// Created by ZZY on 2021/11/30.
//

#ifndef REGISTRATIONVIEWER_COMPOSITECONTROL_H
#define REGISTRATIONVIEWER_COMPOSITECONTROL_H


#include "SingleControlWrapper.h"
#include<list>
#include<optional>

class CompositeControl: public BaseControl {
public:
    CompositeControl(const CompositeControl& control);
    CompositeControl(int id, const string& name, const string& desc, list<SingleControlWrapper> initialList, bool enabled = true);
    const list<SingleControlWrapper> & getSubControlList() const;
    void insertControl(SingleControlWrapper& control);
    const SingleControlWrapper& findControlByName(const string& name);


private:
    list<SingleControlWrapper> subControls;

};


#endif //REGISTRATIONVIEWER_COMPOSITECONTROL_H
