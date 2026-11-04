/* Project2: Smart Campus Navigation and Facility Analytics System

    update: [DOES NOT RUN]
    compile and execute: g++ 
    clean executables: n/a

*/

#include"../include/libraries.h"
using namespace std;

void banner();
string prompt(const string& label);
void menu();

int main(int argc, char* argv[]) {
    banner();
    int option = 0;
    
    //check arguments valid //./campus
    /*if(argc > 1) {
        string testData = argv[1]; 

    }*/
    //load files here

    //continue the menu
    do {
        menu();     //
        string input = prompt("Select an option: ");

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
   getline(cin >> ws, value); 
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