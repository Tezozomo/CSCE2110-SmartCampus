//uses facility class to create and display all the information

#include"../include/facility.h"
using namespace std;

//constructor
Facility::Facility(string facilityID, string facilityName, string building, string category) {

    //normalize all IDs to be uppercased in case of lowercase IDs
    for (char& c : facilityID) {
        c = toupper(static_cast<unsigned char>(c));
    }

    this->facilityID = facilityID;
    this->facilityName = facilityName;
    this->building = building;
    this->category = category;

}

//gets and returns id
string Facility::getID() const {

    return facilityID;

}

//gets and returns facility name
string Facility::getName() const {

    return facilityName;

}

//gets and returns building name
string Facility::getBuilding() const {

    return building;

}

//gets and returns facility category
string Facility::getCategory() const {

    return category;

}

//displays info
void Facility::display() const {

    cout << facilityID << "|" << facilityName << "|" << building << "|" << category << endl;

}