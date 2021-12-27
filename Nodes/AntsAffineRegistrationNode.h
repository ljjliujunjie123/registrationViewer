//
// Created by ZZY on 2021/12/28.
//

#ifndef REGISTRATIONVIEWER_ANTSAFFINEREGISTRATIONNODE_H
#define REGISTRATIONVIEWER_ANTSAFFINEREGISTRATIONNODE_H
#include "AbsNode.h"


class AntsAffineRegistrationNode: public AbsNode {
public:
    AntsAffineRegistrationNode(string name, string desc);
private:
    void initControls();
};


#endif //REGISTRATIONVIEWER_ANTSAFFINEREGISTRATIONNODE_H
