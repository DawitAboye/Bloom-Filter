#include <iostream>
#include <string>
#include "HashSet.h"

using namespace std;
int main(){
    
    HashSet *h = new HashSet();

    h->insert("dawit");
    h->insert("blah");
    h->insert("blah");

    // for(int i= 0; i<100; i++){
    //     if(h->slots[i] == NULL){
    //         cout << "0" << endl;
    //     }
    //     else{
    //         cout << *(h->slots[i]) << endl;
    //     }
    // }

    cout<< h->lookup("dawit") << endl;
    cout << h->lookup("blah") << endl;
    cout<< h->lookup("blah3") << endl;

    return 0;
}