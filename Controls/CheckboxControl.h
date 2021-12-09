//
// Created by ZZY on 2021/12/2.
//

#ifndef REGISTRATIONVIEWER_CHECKBOXCONTROL_H
#define REGISTRATIONVIEWER_CHECKBOXCONTROL_H


class CheckboxControl {
public:
    bool isChecked() const;
    void setChecked(bool checked);

private:
    bool _checked = false;
};


#endif //REGISTRATIONVIEWER_CHECKBOXCONTROL_H
