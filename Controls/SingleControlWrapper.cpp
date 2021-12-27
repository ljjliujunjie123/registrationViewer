//
// Created by ZZY on 2021/12/16.
//

#include "SingleControlWrapper.h"

SingleControlWrapper::SingleControlWrapper(ButtonControl control) {
    _buttonControl = new ButtonControl(control);
    _type = BUTTON;
    _displayName = control.getDisplayName();
    _id = control.getId();
}

SingleControlWrapper::SingleControlWrapper(CheckboxControl control) {
    _checkBoxControl = new CheckboxControl(control);
    _type = CHECKBOX;
    _displayName = control.getDisplayName();
    _id = control.getId();
}

SingleControlWrapper::SingleControlWrapper(ComboBoxControl control) {
    _comboBoxControl = new ComboBoxControl(control);
    _type = COMBO_BOX;
    _displayName = control.getDisplayName();
    _id = control.getId();
}

SingleControlWrapper::SingleControlWrapper(DirectoryFieldControl control) {
    _directoryFieldControl = new DirectoryFieldControl(control);
    _type = DIR_FIELD;
    _displayName = control.getDisplayName();
    _id = control.getId();
}

SingleControlWrapper::SingleControlWrapper(SliderControl control) {
    _sliderControl = new SliderControl(control);
    _type = SLIDER;
    _displayName = control.getDisplayName();
    _id = control.getId();
}

SingleControlWrapper::SingleControlWrapper(SpinBoxControl<int> control) {
    _spinBoxControlI = new SpinBoxControl<int>(control);
    _type = SPIN_BOX_I;
    _displayName = control.getDisplayName();
    _id = control.getId();
}

SingleControlWrapper::SingleControlWrapper(SpinBoxControl<float> control) {
    _spinBoxControlF = new SpinBoxControl<float>(control);
    _type = SPIN_BOX_F;
    _displayName = control.getDisplayName();
    _id = control.getId();
}

SingleControlWrapper::SingleControlWrapper(TripleSpinControl control) {
    _tripleSpinControl = new TripleSpinControl(control);
    _type = TRIPLE_SPIN;
    _displayName = control.getDisplayName();
    _id = control.getId();
}

CONTROL_TYPE SingleControlWrapper::getType() const {
    return _type;
}

ButtonControl& SingleControlWrapper::getButtonControl() {
    checkNull(_buttonControl);
    return *_buttonControl;
}

CheckboxControl &SingleControlWrapper::getCheckboxControl() {
    checkNull(_checkBoxControl);
    return *_checkBoxControl;
}

ComboBoxControl &SingleControlWrapper::getComboBoxControl() {
    checkNull(_comboBoxControl);
    return *_comboBoxControl;
}

DirectoryFieldControl &SingleControlWrapper::getDirectoryFieldControl() {
    checkNull(_directoryFieldControl);
    return *_directoryFieldControl;
}

SliderControl &SingleControlWrapper::getSliderControl() {
    checkNull(_sliderControl);
    return *_sliderControl;
}

const string &SingleControlWrapper::getDisplayName() const {
    return _displayName;
}

int SingleControlWrapper::getId() const {
    return _id;
}

template<> SpinBoxControl<float> &SingleControlWrapper::getSpinBoxControl() {
    checkNull(_spinBoxControlF);
    return *_spinBoxControlF;
}

TripleSpinControl &SingleControlWrapper::getTripleSpinControl() {
    checkNull(_tripleSpinControl);
    return *_tripleSpinControl;
}

template<> SpinBoxControl<int> &SingleControlWrapper::getSpinBoxControl() {
    checkNull(_spinBoxControlI);
    return *_spinBoxControlI;
}



