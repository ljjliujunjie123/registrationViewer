//
// Created by ZZY on 2021/12/9.
//

#ifndef REGISTRATIONVIEWER_CONTROLWRAPPER_H
#define REGISTRATIONVIEWER_CONTROLWRAPPER_H
#include "BaseControl.h"
#include "ButtonControl.h"
#include "CheckboxControl.h"
#include "ComboBoxControl.h"
#include "CompositeControl.h"
#include "DirectoryFieldControl.h"
#include "SliderControl.h"
#include "SpinBoxControl.h"

class ControlWrapper {
public:
    ControlWrapper(ButtonControl& control);
    ControlWrapper(CheckboxControl& control);
    ControlWrapper(ComboBoxControl& control);
    ControlWrapper(CompositeControl& control);
    ControlWrapper(DirectoryFieldControl& control);
    ControlWrapper(SliderControl& control);
    ControlWrapper(SpinBoxControl<int>& control);
    ControlWrapper(SpinBoxControl<float>& control);
    CONTROL_TYPE getType() const;
    const ButtonControl& getButtonControl() const;
    const CheckboxControl& getCheckboxControl() const;
    const ComboBoxControl& getComboBoxControl() const;
    const CompositeControl& getCompositeControl() const;
    const DirectoryFieldControl& getDirectoryFieldControl() const;
    const SliderControl& getSliderControl() const;
    template<typename numberType>
    const SpinBoxControl<numberType>& getSpinBoxControl() const;
private:
    CONTROL_TYPE _type;
    ButtonControl* _buttonControl = nullptr;
    CheckboxControl* _checkBoxControl = nullptr;
    ComboBoxControl* _comboBoxControl = nullptr;
    CompositeControl* _compositeControl = nullptr;
    DirectoryFieldControl* _directoryFieldControl = nullptr;
    SliderControl* _sliderControl = nullptr;
    SpinBoxControl<int>* _spinBoxControlI = nullptr;
    SpinBoxControl<float>* _spinBoxControlF = nullptr;

};




#endif //REGISTRATIONVIEWER_CONTROLWRAPPER_H
