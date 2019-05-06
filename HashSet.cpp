#include "HashSet.h"
#include <iostream>
using namespace std;


// uint64_t myhash(uint64_t input, int m) {
//   return input * (0 + 1) % m;
// }

HashSet::HashSet(){
    nitems = 0;
    nslots = 100;

    //intfn = new ReciprocalHash(0, nslots);
    
    intfn = new DivisionHash(0, nslots);
    strfn = new JenkinsHash();
    strfn2 = new PearsonHash();

    slots = new string* [nslots];

    for(int i=0; i<nslots; i++){
        slots[i] = NULL;
    }
}

HashSet::~HashSet(){
    for(int i = 0; i<nslots; i++){
        if(slots[i] != NULL)
            delete slots[i];
    }
    delete [] slots;
    delete intfn;
    delete strfn2;
    delete strfn;
}

void HashSet::rehash(){
    int oldNumSlots = nslots;
    nslots = nslots*2;

    string** oldSlots = slots;
    slots = new string* [nslots];

    for(int i=0; i<oldNumSlots; i++){
        insert(*(oldSlots[i]));
    }

    //deallocate
    for(int i = 0; i<oldNumSlots; i++){
        if(oldSlots[i] != NULL)
            delete oldSlots[i];
    }
    delete [] oldSlots;
}

void HashSet::insert(const std::string& value){

    if(nitems >= nslots * 0.7){
        rehash();
    }

    uint64_t intVal = strfn->hash(value);
    //cout << intVal << endl;
    uint64_t hashVal = intfn->hash(intVal);
    //cout << hashVal << endl;

    string* ptr = slots[hashVal];
    while(ptr != NULL){
        hashVal++;
        hashVal %= nslots;
        ptr = slots[hashVal];
    }
    //When it leaves this loop our pointer will be NULL

    ptr = new string(value);
    nitems++;
}

bool HashSet::lookup(const std::string& value) const{
    uint64_t intVal = strfn->hash(value);
    uint64_t hashVal = intfn->hash(intVal);

    uint64_t startPt = hashVal;

    //We can't remove items which makes this much easier
    do{
        if(slots[hashVal] == NULL){
            return false;
        }
        else if(*(slots[hashVal]) == value){
            return true;
        }
        hashVal++;
        hashVal %= nslots;

    }while(hashVal != startPt);

    return false;
}

