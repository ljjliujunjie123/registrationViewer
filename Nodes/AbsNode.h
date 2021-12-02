#ifndef ABSNODE_H
#define ABSNODE_H
#include<string>
#include<stdio.h>
#include<list>
#include<functional>
#include <iostream>

using namespace std;

#include "../Controls/AbsControl.h"

enum IO_TYPE {IO_FILEPATH, IO_ANTSIMAGE, IO_ITKIMAGE};


class AbsNode
{
public:
    AbsNode();
    virtual const string& getDisplayName() const;
    list<AbsControl>::const_iterator getControls(){
        return controls.cbegin();
    }
    virtual bool isIOTypeSupported(IO_TYPE type);
    void addStartListener(function<void(void)> l);
    void addFinishListener(function<void(void)> l);

    //0-100 progress
    void addProgressListener(function<void(int)> l);
private:
    list<AbsControl> controls;
    function<void(void)> startListener = [this](){
        cout<<getDisplayName()<<"started"<<endl;
    };

    function<void(void)> finishListener = [this](){
        cout<<getDisplayName()<<endl;
    };
    function<void(int)> progressListener = [this](int progress){
        cout<<getDisplayName()+": progress "<<progress<<endl;
    };



};

#endif // ABSNODE_H
