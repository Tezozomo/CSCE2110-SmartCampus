/* Project2: Smart Campus Navigation and Facility Analytics System

    update: [DOES NOT ALL RUN]
    compile and execute: g++ main.cpp

*/

#include"../include/libraries.h"
#include"../include/departmentTree.h"
#include"../include/campusGraph.h"
using namespace std;

void banner();
string prompt(const string& label);
void menu();

int main(int argc, char* argv[]) {
    banner();
    int option = 0;
    DepartmentTree departmentTree;
    CampusGraph campusGraph;
    string dataFiles = "data";                          //default dir
    
    if(argc > 1) {
        dataFiles = argv[1];            //testdata edge cases

    }
    string bFile = dataFiles + "/buildings.txt";
    string cFile = dataFiles + "/connections.txt";
    campusGraph.loadBuildings(bFile);
    campusGraph.loadConnections(cFile);

    string dFile = dataFiles + "/departments.txt";       //department tree file load
    departmentTree.loadDFile(dFile);            //call fx to load departments file
    
    do {
        menu();
        string input = prompt("Select an option: ");
        istringstream inputStream(input);
        char extraCharacter;
        if (!(inputStream >> option) || (inputStream >> extraCharacter)) {
            cout << "Invalid menu option.\n";
            option = -1;
            continue;
        }

        switch(option) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                campusGraph.display();
                break;
            case 4:
                campusGraph.displayCountsAndDegrees();
                break;
            case 5: {
                string startName = prompt("Enter a starting building: ");
                if (startName.find_first_not_of(" \t\n\r\f\v") ==
                    string::npos) {
                    cout << "Error: building name cannot be blank.\n";
                    break;
                }
                campusGraph.displayReachable(startName);
                break;
            }
            case 6:     //memberC menu 6-9 [TREE-1 - TREE-8]
                //add
                break;
            case 7:
                //search
                break;
            case 8:
                //hierarchy
                break;
            case 9:
                //preorder
                break;
            case 0:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Option not available.";

        }
    } while(option != 0);

    return 0;

}

void banner() {
   // show banner
   cout << "+--------------------------------------------------------------+\n"
        << "|               Computer Science and Engineering               |\n"
        << "|            CSCE 2110 - Foundation of Data Structures         |\n"
        << "|                                                              |\n"
        << "|                Project 2 Smart Campus Navigation             |\n"
        << "|                                                              |\n"
        << "|                  Section 400 Group Members:                  |\n"
        << "|             Dalen Ragsdale dalenragsdale@my.unt.edu          |\n"
        << "|               Ivan Garcia ivangarcia4@my.unt.edu             |\n"
        << "|              Trevor Sipes trevorsipes@my.unt.edu             |\n"
        << "+--------------------------------------------------------------+\n\n\n";

}

string prompt(const string& label) {
   // read user input
   cout << label;
   string value;
   getline(cin, value);
   return value;

}

void menu() {
   cout << "+--------------------------------------------------------------------------+\n"
        << "|                     Smart Campus System                                  |\n"
        << "+--------------------------------------------------------------------------+\n"
        << "|   1 - View facilities                   6 - Add department               |\n"
        << "|   2 - Search facility by ID             7 - Search department            |\n"
        << "|   3 - View campus graph                 8 - Display department hierarchy |\n"
        << "|   4 - Display graph counts and degrees  9 - Run preorder traversal       |\n"
        << "|   5 - Find reachable building           0 - Exit                         |\n"
        << "+--------------------------------------------------------------------------+\n\n";

}