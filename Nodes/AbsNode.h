#ifndef ABSNODE_H
#define ABSNODE_H
#include<string>
#include<stdio.h>
#include<list>
#include<functional>
#include <iostream>

using namespace std;

#include "../Controls/BaseControl.h"
#include "../Controls/ControlWrapper.h"

enum IO_TYPE {IO_FILEPATH, IO_ANTSIMAGE, IO_ITKIMAGE};


class AbsNode
{
public:
    AbsNode(const string& name, const string& desc="");
    virtual const string& getDisplayName() const;
    const list<ControlWrapper>& getControls() const{
        return controls;
    }
    void addStartListener(function<void(void)> l);
    void addFinishListener(function<void(void)> l);

    //0-100 progress
    void addProgressListener(function<void(int)> l);
    void registerUpdateListener(function<void(void)> l);

protected:
    string displayName;
    list<ControlWrapper> controls;
    function<void(void)> startListener = [this](){
        cout<<getDisplayName()<<"started"<<endl;
    };

    function<void(void)> finishListener = [this](){
        cout<<getDisplayName()<<endl;
    };
    function<void(int)> progressListener = [this](int progress){
        cout<<getDisplayName()+": progress "<<progress<<endl;
    };
    function<void(void)> updateListener;

};

#endif // ABSNODE_H
