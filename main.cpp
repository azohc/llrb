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

        //llrb.traverse();

        for(int i=0;i<1000;i++){
            if(llrb.search(keys[i])!=vals[i]){
                return -1;
            }
        }

        for(int i=0;i<500;i++)
            llrb.remove(keys[i]);

        for(int i=500;i<1000;i++){
            if(llrb.search(keys[i])!=vals[i])
                return -1;
            
        }
    }

    std::cout<<"Good"<<std::endl;
}


// int main(){
    
//     LLRBTree<int, int> t = LLRBTree<int, int>(1,1); 

//     t.insert(2,2);
//     t.insert(4,4);
//     t.insert(5,5);
//     t.insert(7,7);
//     t.insert(8,8);  
//     t.insert(11,11);
//     t.insert(14,14);
//     t.insert(15,15);

//     t.insert(5, 11);
//     t.insert(-11, 11);


//     list<int> k = t.get_keys_inorder();
//     list<int>::const_iterator kit = k.cbegin();

//     list<int> v = t.get_values_inorder();
//     list<int>::const_iterator vit = v.cbegin();

//     while(kit != k.cend())
//         cout << "(" << *kit++ << ", " << *vit++ << "),";

//     cout << endl;   

//     // try{
//     // cout << "inexistent key, 91: t.search(91) returns " << t.search(91) << endl << endl;
//     // } catch (std::exception &e) {
//     //     std::cerr << e.what() << endl;
//     // }

//     // int keys = 5;
//     // if(t.contains(keys))
//     //     cout << "Tree contains key-value pair (" << keys << ", " << t.search(keys) << ")." << endl;
//     // else
//     //     cout << "No matches for key " << keys << endl;
  
    
//     return 0;
// }


