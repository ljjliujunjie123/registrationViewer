//
// Created by ZZY on 2021/12/27.
//

#include "MultiTypeControl.h"

MultiTypeControl::MultiTypeControl(int id, string name, string desc, map<string, list<SingleControlWrapper>> controlMap,
                                   bool enabled): BaseControl(id, name, desc, enabled) {

}

const map<string, list<SingleControlWrapper>> &MultiTypeControl::getSubControlMap() const {
    return subControlMap;
}
