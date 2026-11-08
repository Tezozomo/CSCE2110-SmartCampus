//creates the custom hash table that stores facility class objects

#include "../include/hashTable.h"

using namespace std;

//constructing the hash table
HashTable::HashTable(int size) {

    if (size <= 0) {
        size = 10;
    }

    //setting variables
    capacity = size;
    entries = 0;
    collisions = 0;
    hashTable.resize(capacity);
}

//finds index for the bucket by using facility IDs
int HashTable::hashFunction(string key) const {

    int h = 0;

    //normalize all IDs to be uppercased in case of lowercase IDs
    for (char& c : key) {
        c = toupper(static_cast<unsigned char>(c));
    }

    //hash funct
    for (char c : key) {
        h = (h * 31 + c) % capacity;
    }
    return h;
}

//adds facility to table
bool HashTable::insert(const Facility& facility) {

    string key = facility.getID();
    //normalize all IDs to be uppercased in case of lowercase IDs
    for (char& c : key) {
        c = toupper(static_cast<unsigned char>(c));
    }

    int index = hashFunction(key);
    //this for loop checks to see if any IDs are duplicates of eachother
    for (const Facility& existing : hashTable[index]) {

        if (existing.getID() == key) {

            return false;

        }
    }
    //increment collisions if theres a problem with a bucket containing 2 facilities
    if (!hashTable[index].empty()) {

        collisions++;

    }

    hashTable[index].push_back(facility);
    entries++;
    return true;


}
//uses the facilities ID to "search" for it
const Facility* HashTable::search(string facilityID) const {

    //normalize all IDs to be uppercased in case of lowercase IDs
    for (char& c : facilityID) {
        c = toupper(static_cast<unsigned char>(c));
    }

    int index = hashFunction(facilityID);
    //searches the bucket we have the index for
    for (const Facility& facility : hashTable[index]) {
        //returns the facility if the IDs match
        if (facility.getID() == facilityID) {
            
            return &facility;

        }

    }
    return nullptr;
}
//returns capacity
int HashTable::getCapacity() const {

    return capacity;

}
//returns entries
int HashTable::getEntries() const {

    return entries;

}
//returns collisions
int HashTable::getCollisions() const {

    return collisions;

}