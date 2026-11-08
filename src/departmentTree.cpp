/*

*/
#include"../include/departmentTree.h"
using namespace std;

//constructor
DepartmentTree::DepartmentTree() {
    root = nullptr;

}
//destructor
DepartmentTree::~DepartmentTree() {
    destructTree(root);

}
//load
void DepartmentTree::loadDFile(const string& dFile) {
    ifstream depFile(dFile);            //create stream var

    if(!depFile.is_open()) {
        cout << "Error opening departments file.\n";        //check file work
        return;

    }
    
    string line;
    int accept = 0;
    int reject = 0;

    while(getline(depFile, line)) {
        if(line.empty() || line[0] == '#') {
            continue;                   //skip

        }
        
        stringstream ss(line);
        string departmentName, parentName;
        getline(ss, departmentName, '|');       //parse dept/parent
        getline(ss, parentName, '|');

        if(root == nullptr) {
            root = new DepartmentNode(departmentName, nullptr);
            accept++;

        }
        else{
            DepartmentNode* parentNode = searchNode(root, parentName);

            if(parentNode != nullptr) {
                DepartmentNode* newChild = new DepartmentNode(departmentName, parentNode);
                parentNode->child.push_back(newChild);          //attach child
                accept++;

            }
            else {
                cout << "No parent found.\n";
                reject++;

            }
        }
    }
    depFile.close();        //file closed

    cout << dFile << ":" << accept << " accepted, " << reject << " recjected\n";        //LOAD-4 summary

}
//add
void DepartmentTree::addD(const string& name, const string& parentNode) {
    //
    if(root == nullptr) {
        root = new DepartmentNode(name);        //create root

    }
    else {
        if(searchNode(root, name) != nullptr) {
            cout << "Department exists,\n";         //make sure same or not
        
        }
        else {
            DepartmentNode* parent = searchNode(root, parentNode);      //find parent
            if(parent == nullptr) {
                cout << "Parent not found.\n";

            }
            else {
                DepartmentNode* newNode = new DepartmentNode(name, parent);
                parent->child.push_back(newNode);           //add child to vector

            }
        }
    }
}
//search
void DepartmentTree::searchD(const string& name) {
    DepartmentNode* foundNode = searchNode(root, name);             //searching
    if(foundNode == nullptr) {
        cout << "Department not found.\n";

    }
    else {
        int depth = 0;
        DepartmentNode* currNode = foundNode;           //temp while incrementing depth
        while(currNode->parent != nullptr) {
            currNode = currNode->parent;                //has a parent 
            depth++;

        }

        string parentName;
        if(foundNode->parent == nullptr) {
            parentName = "None";
        
        }
        else {
            DepartmentNode* parentNode = foundNode->parent;     //get parent
            parentName = parentNode->name;                      //name of node

        }
        
        cout << "Name: " << foundNode->name << endl
             << "Parent: " << parentName << endl
             << "child count: " << foundNode->child.size() << endl
             << "Depth: " << depth << endl;

    }
}
//print call
void DepartmentTree::printTree() {
    if(root == nullptr) {
        cout << "No department to load.\n";     //nothing to load

    }
    else {
        printTree(root, 0);         //access private traversal fx
    
    }
}
//pre-order
void DepartmentTree::printPreOrder() {
    if(root == nullptr) {
        cout << "No epartment to load\n";

    }
    else {
        printPreOrder(root);            //access pre-order

    }
}

////private node fx's
//search
DepartmentNode* DepartmentTree::searchNode(DepartmentNode* currNode, const string& name) {
    if(currNode == nullptr) {                       //empty?
        return nullptr;

    }
    if(currNode->name == name) {
        return currNode;                    //match

    }
    for(int i = 0; i < currNode->child.size(); i++) {                               //loop child of curr
        DepartmentNode* foundNode = searchNode(currNode->child[i], name);           //check child
        if(foundNode != nullptr) {
            return foundNode;

        }
    }
    return nullptr;

}
//print traversal
void DepartmentTree::printTree(DepartmentNode* currNode, int depth) {
    for(int i = 0; i < depth * 4; i++) {            //4 spaces for depth TREE-5
        cout << " ";

    }
    cout << currNode->name << endl;

    for(int i = 0; i < currNode->child.size(); i++) {           //recursive visit children of dept
        printTree(currNode->child[i], depth + 1);               

    }
}
//print pre-order
void DepartmentTree::printPreOrder(DepartmentNode* currNode) {
    cout << currNode->name << endl;
    for(int i = 0; i < currNode->child.size(); i++) {
        printPreOrder(currNode->child[i]);                  //print descendants

    }
}
//managee mem
void DepartmentTree::destructTree(DepartmentNode* currNode) {
    if(currNode == nullptr) {
        return;         //empty

    }
    for(int i = 0; i < currNode->child.size(); i++) {
        DepartmentNode* nextChild = currNode->child[i];
        destructTree(nextChild);            //recursively delete child

    }
    delete currNode;        //parent delete

}