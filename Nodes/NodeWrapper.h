//
// Created by ZZY on 2021/12/16.
//

#ifndef REGISTRATIONVIEWER_NODEWRAPPER_H
#define REGISTRATIONVIEWER_NODEWRAPPER_H
#include "Tests/TestNode.h"
#include "AntsAffineRegistrationNode.h"
#include "AntsRigidRegistrationNode.h"
#include "AntsSyNRegistrationNode.h"

enum NODE_TYPE{ TEST,
        ANTS_CONFIG,
        ANTS_TRANSFORM_RIGID,
        ANTS_TRANSFORM_AFFINE,
        ANTS_TRANSFROM_BSPLINE,
        ANTS_TRANSFORM_SYN,
        ANTS_TRANFROM_BSPLINESYN
};
class NodeWrapper {
//  Constructors:
public:
    NodeWrapper(TestNode node);
    NodeWrapper(AntsAffineRegistrationNode node);
    NodeWrapper(AntsRigidRegistrationNode node);
    NodeWrapper(AntsSyNRegistrationNode node);


//  Methods:
public:
    NODE_TYPE getType() const;
    const string & getDisplayName() const;
    inline bool operator==(const NodeWrapper& rhs);
    AbsNode& getBaseNode() {
        return baseNode;
    }
private:
    NODE_TYPE _type;
    string _displayName;
    AbsNode baseNode;

    TestNode* _testNode = nullptr;
    AntsAffineRegistrationNode* _antsAffineNode = nullptr;
    AntsRigidRegistrationNode* _antsRigidNode = nullptr;
    AntsSyNRegistrationNode* _antsSyNNode = nullptr;
};


#endif //REGISTRATIONVIEWER_NODEWRAPPER_H
