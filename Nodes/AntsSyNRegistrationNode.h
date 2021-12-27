//
// Created by ZZY on 2021/12/28.
//

#ifndef REGISTRATIONVIEWER_ANTSSYNREGISTRATIONNODE_H
#define REGISTRATIONVIEWER_ANTSSYNREGISTRATIONNODE_H
#include "AbsNode.h"

class AntsSyNRegistrationNode: public AbsNode{
public:
    AntsSyNRegistrationNode(string name, string desc);

private:
    void initControls();
};


#endif //REGISTRATIONVIEWER_ANTSSYNREGISTRATIONNODE_H
