#ifndef ABSCONTROL_H
#define ABSCONTROL_H
#include<string>
#include<stdio.h>

using namespace std;


class AbsControl
{
public:
    AbsControl(const string& name);
    const string& getDisplayName() const;
    void setEnabled(bool enabled){
        _enabled = enabled;
    }

protected:
    bool _enabled = true;
    string displayName;

};

#endif // ABSCONTROL_H
