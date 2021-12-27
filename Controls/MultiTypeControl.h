//
// Created by ZZY on 2021/12/27.
//

#ifndef REGISTRATIONVIEWER_MULTITYPECONTROL_H
#define REGISTRATIONVIEWER_MULTITYPECONTROL_H
#include "BaseControl.h"
#include "SingleControlWrapper.h"
#include<map>
#include<list>

class MultiTypeControl: public BaseControl {
public:
    MultiTypeControl(int id, string name, string desc, map<string, list<SingleControlWrapper>> controlMap, bool enabled = true);
    const map<string, list<SingleControlWrapper>>& getSubControlMap() const;

private:
    map<string, list<SingleControlWrapper>> subControlMap;

};


#endif //REGISTRATIONVIEWER_MULTITYPECONTROL_H