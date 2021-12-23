//
// Created by ZZY on 2021/12/9.
//

#include "ControlWrapper.h"


const CompositeControl &ControlWrapper::getCompositeControl() const {
    return *_compositeControl;
}

ControlWrapper::ControlWrapper(CompositeControl control) {
    _compositeControl = new CompositeControl(control);
    _type = COMPOSITE;
    _displayName = control.getDisplayName();
    _id = control.getId();
}

ControlWrapper::ControlWrapper(const ControlWrapper& cw) {
    if(cw.getType() == COMPOSITE) _compositeControl = new CompositeControl(cw.getCompositeControl());
}
