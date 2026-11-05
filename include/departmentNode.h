/*

*/

#ifndef DEPARTMENT_NODE_H
#define DEPARTMENT_NODE_H

#include"libraries.h"
using namespace std;

struct DepartmentNode {         ///nodes of tree
    string name;
    DepartmentNode* parent;
    vector<DepartmentNode*> child;          //vector of child ptrs

    //constructor new node
    DepartmentNode(string dName, DepartmentNode* parentNode = nullptr) {
        name = dName;
        parent = parentNode;

    }
};

#endif