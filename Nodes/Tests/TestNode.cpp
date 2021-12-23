//
// Created by ZZY on 2021/12/16.
//

#include "TestNode.h"

TestNode::TestNode(const string &name, const string &desc) : AbsNode(name, desc) {
    initControls();
}

void TestNode::initControls() {
    ControlWrapper composite = CompositeControl(1, "Basic Composite", "Basic Composite Desc", {
            ControlWrapper(SliderControl(2,"Slider", "Slider Desc", {0,255})),
            ControlWrapper(CheckboxControl(3,"CheckBox", "CheckBox Desc", true)),
            ControlWrapper(ComboBoxControl(4,"ComboBox", "ComboBox Desc", {"Hello", "World", "Registration"}, "World", true))
    });
    auto initControls = {
            ControlWrapper(ButtonControl(5,"Button", "Button Description", IC_MINUS, true)),
            ControlWrapper(CheckboxControl(6,"CheckBox", "CheckBox Desc", false, false)),
            ControlWrapper(ComboBoxControl(7,"ComboBox", "ComboBox Desc", {"Hello", "World", "Registration"}, "World", true)),
            composite,
            ControlWrapper(DirectoryFieldControl(8,"Dir field", "Dir field desc")),
            ControlWrapper(SliderControl(9,"Slider", "Slider Desc", {9,255})),
            ControlWrapper(SpinBoxControl<int>(10,"Spin box <int>", "Spin box int desc", {5,100},false)),
            ControlWrapper(SpinBoxControl<float>(11,"Spin box <float>", "Spin box float desc", {0.5,1.0}))
    };
    controls = initControls;
}

string TestNode::generateArgs() const {
    string call = "";
    for (auto control : controls){
        switch(control.getId()){
            case 1: generateCmdLineComposite(control.getCompositeControl(), call); break;
            case 6: call += (string(" -checked ") + (control.getCheckboxControl().isChecked()? "true" : "false")); break;
            case 7: call += (" -comboSelected " + control.getComboBoxControl().getSelected()); break;
            case 8: call += (" -dir " + control.getDirectoryFieldControl().getDir()); break;
            case 9: call += (" -sliderVal " + to_string(control.getSliderControl().getValue())); break;
            case 10: call += (" -sbinIntVal " + to_string(control.getSpinBoxControl<int>().getValue())); break;
            case 11: call += (" -sbinFloatVal " + to_string(control.getSpinBoxControl<float>().getValue())); break;
        }
    }
    return call;
}

void TestNode::generateCmdLineComposite(const CompositeControl &control, string &s) const {
    s += " -composite [";
    for(auto it: control.getSubControlList()){
        switch(it.getId()){
            case 2: s += (" sliderVal=" + to_string(it.getSliderControl().getValue())); break;
            case 3: s += (string(", checked=") + (it.getCheckboxControl().isChecked()? "true" : "false")); break;
            case 4: s += (", comboSelected=" + it.getComboBoxControl().getSelected()); break;
        }
    }
    s += " ]";
}




