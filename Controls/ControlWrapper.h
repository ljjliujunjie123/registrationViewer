//
// Created by ZZY on 2021/12/9.
//

#ifndef REGISTRATIONVIEWER_CONTROLWRAPPER_H
#define REGISTRATIONVIEWER_CONTROLWRAPPER_H
#include "SingleControlWrapper.h"
#include "CompositeControl.h"
#include "MultiTypeControl.h"

class ControlWrapper: public SingleControlWrapper{
public:

    ControlWrapper(CompositeControl control);
    ControlWrapper(MultiTypeControl control);

    ControlWrapper(ButtonControl control): SingleControlWrapper(move(control)){};
    ControlWrapper(CheckboxControl control): SingleControlWrapper(move(control)){};
    ControlWrapper(ComboBoxControl control): SingleControlWrapper(move(control)){};
    ControlWrapper(DirectoryFieldControl control): SingleControlWrapper(move(control)){};
    ControlWrapper(SliderControl control): SingleControlWrapper(move(control)){};
    ControlWrapper(SpinBoxControl<int> control): SingleControlWrapper(move(control)){};
    ControlWrapper(SpinBoxControl<float> control): SingleControlWrapper(move(control)){};
    ControlWrapper(TripleSpinControl control): SingleControlWrapper(control){};

    const CompositeControl& getCompositeControl() const;
    MultiTypeControl& getMultiTypeControl();

private:
    CompositeControl* _compositeControl = nullptr;
    MultiTypeControl* _multiTypeControl = nullptr;
};




#endif //REGISTRATIONVIEWER_CONTROLWRAPPER_H
