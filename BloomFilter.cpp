#include "BloomFilter.h"

#define UNUSED(x) (void)(x)

BloomFilter::BloomFilter(int k, int m, std::string strfn, std::string intfn){
    UNUSED(strfn);
    UNUSED(intfn);
    this->k = k;
    this->m = m;

    this->strfn = new PearsonHash();
    this->intfns = new IntegerHash*[k];

    for(int i=0; i<k; i++){
        intfns[i] = new SquareRootHash(i, m);
    }

    bits = new uint64_t();
}

BloomFilter::~BloomFilter(){
    for(int i=0; i<k; i++){
        delete intfns[k];
    }

    delete [] intfns;
    delete strfn;
    delete bits;
}

void BloomFilter::insert(const std::string& value){
    uint64_t intVal = strfn->hash(value);
    //cout << intVal << endl;
    for(int i=0; i<k; i++){
        uint64_t hashVal = intfns[i]->hash(intVal);
        *bits |= 1UL << hashVal;
    }
}

bool BloomFilter::lookup(const std::string& value) const{
    UNUSED(value);
    return true;
    uint64_t intVal = strfn->hash(value);
    for(int i=0; i<k; i++){
        uint64_t hashVal = intfns[i]->hash(intVal);
        
        if(! (*bits & (1 << (hashVal - 1))))
            return false; 
    }
    return true;
}
