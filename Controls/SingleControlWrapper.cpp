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

CONTROL_TYPE SingleControlWrapper::getType() const {
    return _type;
}

const ButtonControl& SingleControlWrapper::getButtonControl() const {
    checkNull(_buttonControl);
    return *_buttonControl;
}

const CheckboxControl &SingleControlWrapper::getCheckboxControl() const {
    checkNull(_checkBoxControl);
    return *_checkBoxControl;
}

const ComboBoxControl &SingleControlWrapper::getComboBoxControl() const {
    checkNull(_comboBoxControl);
    return *_comboBoxControl;
}

const DirectoryFieldControl &SingleControlWrapper::getDirectoryFieldControl() const {
    checkNull(_directoryFieldControl);
    return *_directoryFieldControl;
}

const SliderControl &SingleControlWrapper::getSliderControl() const {
    checkNull(_sliderControl);
    return *_sliderControl;
}

const string &SingleControlWrapper::getDisplayName() const {
    return _displayName;
}

int SingleControlWrapper::getId() const {
    return _id;
}

template<> const SpinBoxControl<float> &SingleControlWrapper::getSpinBoxControl() const {
    checkNull(_spinBoxControlF);
    return *_spinBoxControlF;
}

template<> const SpinBoxControl<int> &SingleControlWrapper::getSpinBoxControl() const {
    checkNull(_spinBoxControlI);
    return *_spinBoxControlI;
}



