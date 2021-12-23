//
// Created by ZZY on 2021/12/16.
//

#ifndef REGISTRATIONVIEWER_SINGLECONTROLWRAPPER_H
#define REGISTRATIONVIEWER_SINGLECONTROLWRAPPER_H
#include "BaseControl.h"
#include "ButtonControl.h"
#include "CheckboxControl.h"
#include "ComboBoxControl.h"
#include "DirectoryFieldControl.h"
#include "SliderControl.h"
#include "SpinBoxControl.h"


class SingleControlWrapper {
public:
    SingleControlWrapper()= default;
    SingleControlWrapper(const SingleControlWrapper& cw);
    SingleControlWrapper(ButtonControl control);
    SingleControlWrapper(CheckboxControl control);
    SingleControlWrapper(ComboBoxControl control);
    SingleControlWrapper(DirectoryFieldControl control);
    SingleControlWrapper(SliderControl control);
    SingleControlWrapper(SpinBoxControl<int> control);
    SingleControlWrapper(SpinBoxControl<float> control);
    CONTROL_TYPE getType() const;
    const string& getDisplayName() const;
    int getId() const;
    const ButtonControl& getButtonControl() const;
    const CheckboxControl& getCheckboxControl() const;
    const ComboBoxControl& getComboBoxControl() const;
    const DirectoryFieldControl& getDirectoryFieldControl() const;
    const SliderControl& getSliderControl() const;
    template<typename numberType>
    const SpinBoxControl<numberType>& getSpinBoxControl() const;
protected:
    CONTROL_TYPE _type;
    string _displayName;
    int _id;
    ButtonControl* _buttonControl = nullptr;
    CheckboxControl* _checkBoxControl = nullptr;
    ComboBoxControl* _comboBoxControl = nullptr;
    DirectoryFieldControl* _directoryFieldControl = nullptr;
    SliderControl* _sliderControl = nullptr;
    SpinBoxControl<int>* _spinBoxControlI = nullptr;
    SpinBoxControl<float>* _spinBoxControlF = nullptr;

};

#endif //REGISTRATIONVIEWER_SINGLECONTROLWRAPPER_H
