/*NFR-1

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
        void addD(const string& name, const string& parentNode);        //TREE-3
        void searchD(const string& name);                               //TREE-4
        void printTree();                                        //parameters diff no conflict
        void printPreOrder();

        DepartmentNode* root;           //node ptr that hold root
        
    private:
        //node split prvt to hide complexity from main
        DepartmentNode* searchNode(DepartmentNode* currNode, const string& name);        
        void printTree(DepartmentNode* currNode, int depth);      //TREE-5 hierarchy
        void printPreOrder(DepartmentNode* currNode);             //TREE-6 traversal
        void destructTree(DepartmentNode* currNode);              //does actual deleteing of nodes

};

#endif