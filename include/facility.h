//construct Facility class with id, name, buildilng and category for the hash table to store

#ifndef FACILITY_H
#define FACILITY_H

#include "libraries.h"

using namespace std;

class Facility {
    private:

        string facilityID;
        string facilityName;
        string building;
        string category;

    public:
    
        Facility(string facilityID, string facilityName, string building, string category); //Constructor

        //get functions
        string getID() const;
        string getName() const;
        string getBuilding() const;
        string getCategory() const;
        //display full information
        void display() const;

};

#endif