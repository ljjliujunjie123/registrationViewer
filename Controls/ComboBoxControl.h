//
// Created by ZZY on 2021/12/2.
//

#ifndef REGISTRATIONVIEWER_COMBOBOXCONTROL_H
#define REGISTRATIONVIEWER_COMBOBOXCONTROL_H
#include "BaseControl.h"
#include<vector>


class ComboBoxControl final: public BaseControl{
public:

    ComboBoxControl(int id, const string &name, const string& desc, vector<string>&& options, const string& defaultOpt, bool enabled=true);
    const vector<string>& getOptionList() const;
    const string& getDefaultOption() const;
    void setSelected(int index);
    const string& getSelected() const;
    void setValueChangedListener(function<void(string)> l );

private:
    vector<string> optionList;
    string defaultOption;
    string currentSelected;
    function<void(string)> onValueChangeListener;
};


#endif //REGISTRATIONVIEWER_COMBOBOXCONTROL_H
