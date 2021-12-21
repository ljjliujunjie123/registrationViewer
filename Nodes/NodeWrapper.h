//
// Created by ZZY on 2021/12/16.
//

#ifndef REGISTRATIONVIEWER_NODEWRAPPER_H
#define REGISTRATIONVIEWER_NODEWRAPPER_H
#include "Tests/TestNode.h"

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


//  Methods:
public:
    NODE_TYPE getType() const;
    const string & getDisplayName() const;
    inline bool operator==(const NodeWrapper& rhs);
    NodeWrapper(TestNode& node);
    const AbsNode& getBaseNode() const {
        return baseNode;
    }
private:
    NODE_TYPE _type;
    string _displayName;
    AbsNode baseNode;

    TestNode* _testNode = nullptr;
};


#endif //REGISTRATIONVIEWER_NODEWRAPPER_H
