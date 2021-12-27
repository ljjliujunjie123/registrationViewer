//
// Created by ZZY on 2021/12/28.
//

#ifndef REGISTRATIONVIEWER_ANTSRIGIDREGISTRATIONNODE_H
#define REGISTRATIONVIEWER_ANTSRIGIDREGISTRATIONNODE_H
#include "AbsNode.h"

class AntsRigidRegistrationNode: public AbsNode {
public:
    AntsRigidRegistrationNode(string name, string desc);

private:
    void initControls();
};


#endif //REGISTRATIONVIEWER_ANTSRIGIDREGISTRATIONNODE_H
