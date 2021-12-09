//
// Created by ZZY on 2021/12/9.
//

#include "ControlWrapper.h"


ControlWrapper::ControlWrapper(ButtonControl &control) {
    _buttonControl = &control;
    _type = BUTTON;
}

ControlWrapper::ControlWrapper(CheckboxControl &control) {
    _checkBoxControl = &control;
    _type = CHECKBOX;
}

ControlWrapper::ControlWrapper(ComboBoxControl &control) {
    _comboBoxControl = &control;
    _type = COMBO_BOX;
}

ControlWrapper::ControlWrapper(CompositeControl &control) {
    _compositeControl = &control;
    _type = COMPOSITE;
}

ControlWrapper::ControlWrapper(DirectoryFieldControl &control) {
    _directoryFieldControl = &control;
    _type = DIR_FIELD;
}

ControlWrapper::ControlWrapper(SliderControl &control) {
    _sliderControl = &control;
    _type = SLIDER;
}

ControlWrapper::ControlWrapper(SpinBoxControl<int> &control) {
    _spinBoxControlI = &control;
    _type = SPIN_BOX_I;
}

ControlWrapper::ControlWrapper(SpinBoxControl<float> &control) {
    _spinBoxControlF = &control;
    _type = SPIN_BOX_F;
}

CONTROL_TYPE ControlWrapper::getType() const {
    return _type;
}

void checkNull(void* ptr){
    if(ptr == nullptr) throw runtime_error("NullPtr retrieving from ControlWrapper");
}

const ButtonControl &ControlWrapper::getButtonControl() const {
    checkNull(_buttonControl);
    return *_buttonControl;
}

const CheckboxControl &ControlWrapper::getCheckboxControl() const {
    checkNull(_checkBoxControl);
    return *_checkBoxControl;
}

const ComboBoxControl &ControlWrapper::getComboBoxControl() const {
    checkNull(_comboBoxControl);
    return *_comboBoxControl;
}

const CompositeControl &ControlWrapper::getCompositeControl() const {
    checkNull(_compositeControl);
    return *_compositeControl;
}

const DirectoryFieldControl &ControlWrapper::getDirectoryFieldControl() const {
    checkNull(_directoryFieldControl);
    return *_directoryFieldControl;
}

const SliderControl &ControlWrapper::getSliderControl() const {
    checkNull(_sliderControl);
    return *_sliderControl;
}

template<typename numberType>
const SpinBoxControl<numberType> &ControlWrapper::getSpinBoxControl() const {
    if(is_same<numberType, int>::value){
        checkNull(_spinBoxControlI);
        return *_spinBoxControlI;
    } else if(is_same<numberType, int>::value){
        checkNull(_spinBoxControlF);
        return *_spinBoxControlF;
    }
    else throw invalid_argument("Invalid type of SpinControl, only int or float is allowed.");
}




