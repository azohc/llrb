#include "LLRBTree.h"
#include <iostream>

#include <vector>
#include <unordered_map>

using std::list;
using std::iterator;
using std::cin;
using std::cout;
using std::endl;




int main(){
    for(int test=0;test<500;test++){
        LLRBTree<int,int> llrb;
        std::unordered_map<int, bool> keymap;
        std::vector<int> keys;
        std::vector<int> vals;

        for(int i=0;i<1000;i++){
            int newkey = rand();
            while(keymap.count(newkey) == 1)
                newkey = rand();

            keys.push_back(newkey);
            vals.push_back(rand()+1);
            llrb.insert(keys.back(),vals.back());
            keymap.insert(std::pair<int,bool>(newkey, true));
        }


        for(int i=0;i<1000;i++){
            if(llrb.get(keys[i])!=vals[i]){
                return -1;
            }
        }

        for(int i=0;i<1000;i++){
            llrb.remove(keys[i]);
            keys.pop_back();
        }    
    }

    std::cout<<"Good"<<std::endl;
    return 0;
}




