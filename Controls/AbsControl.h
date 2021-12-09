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
    const string& getDescription() const;
    void setDescription(const string& desc);

protected:
    bool _enabled = true;
    string displayName;
    string description;

};

#endif // ABSCONTROL_H
