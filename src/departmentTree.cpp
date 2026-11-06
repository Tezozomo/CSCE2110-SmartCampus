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

void DepartmentTree::destructTree(DepartmentNode* currNode) {
    if(currNode == nullptr) {
        return;         //emptyy

    }
    for(int i = 0; i < currNode->child.size(); i++) {
        DepartmentNode* nextChild = currNode->child[i];
        destructTree(nextChild);            //recursively delete child

    }
    delete currNode;        //parent delete

}
//search
DepartmentNode* DepartmentTree::searchNode(DepartmentNode* currNode, const string& name) {
    if(currNode == nullptr) {
        return nullptr;

    }
    if(currNode->name == name) {
        return currNode;

    }
    for(int i = 0; i < currNode->child.size(); i++) {
        DepartmentNode* found = searchNode(currNode->child[i], name);
        if(found != nullptr) {
            return found;

        }
    }
    return nullptr;

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