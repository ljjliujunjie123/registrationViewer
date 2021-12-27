//
// Created by ZZY on 2021/12/9.
//

#include "ControlWrapper.h"


const CompositeControl &ControlWrapper::getCompositeControl() const {
    checkNull(_compositeControl);
    return *_compositeControl;
}

ControlWrapper::ControlWrapper(CompositeControl control) {
    _compositeControl = new CompositeControl(control);
    _type = COMPOSITE;
    _displayName = control.getDisplayName();
    _id = control.getId();
}

ControlWrapper::ControlWrapper(MultiTypeControl control) {
    _multiTypeControl = new MultiTypeControl(control);
    _type = MULTI_TYPE;
    _displayName = control.getDisplayName();
    _id = control.getId();
}

const MultiTypeControl &ControlWrapper::getMultiTypeControl() const {
    checkNull(_multiTypeControl);
    return *_multiTypeControl;
}

