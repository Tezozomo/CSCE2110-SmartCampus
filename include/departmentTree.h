/*

*/

#ifndef DEPARTMENT_TREE_H
#define DEPARTMENT_TREE_H

#include"libraries.h"
#include"departmentNode.h"
using namespace std;

class DepartmentTree {
    public:
        DepartmentTree();       //default constuctor
        ~DepartmentTree();      //destructor 

        void loadDFile(const string& dFile);                            //TREE-2 departments loaded

    private:
        //node split prvt to hide complexity from main
        DepartmentNode* root;           //node ptr that hold root

};

#endif