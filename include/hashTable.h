//creates own hash table to store facility class objects
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "libraries.h"
#include "facility.h"

using namespace std;

class HashTable {
    private:

        vector<vector<Facility>> hashTable;
        int capacity;
        int entries;
        int collisions;
        int hashFunction(string key) const; //creates the index

    public:

        HashTable(int size = 10); //constructor
        bool insert(const Facility& facility); //insert facility
        const Facility* search(string facilityID) const;//searches for facilityID
        int getCapacity() const;
        int getEntries() const;
        int getCollisions() const;

    };

#endif