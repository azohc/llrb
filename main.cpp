#include "LLRBTree.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include <vector>
#include <unordered_map>

// using std::list;
// using std::iterator;
using std::cin;
using std::cout;
using std::endl;



int test(int n)
{
    LLRBTree<int,int> llrb;
    std::unordered_map<int, bool> keymap;
    std::vector<int> keys;
    // std::vector<int> vals;
    

    for(int test = 0; test < n; test++)
    {
        int* values = new int[1000];

        for (int i = 0; i < 1000; i++)
        {
            int newkey = rand() % 1000;

            //Comment these next two to ignore duplicate keys
            while(keymap.count(newkey))
                newkey = rand() % 1000;

            keys.push_back(newkey);
            // vals.push_back(rand()+1);
            values[newkey] = rand() % 9999;
            // llrb.insert(keys.back(),vals.back());
            llrb.insert(newkey, values[newkey]);
            keymap.insert(std::pair<int,bool>(newkey, true));
        }


        // for(int i=0;i<1000;i++)
        while (!keys.empty())
        {
            // if(llrb.get(keys[i])!=vals[i])
            int key = keys.back();
            if(llrb.get(key)!=values[key])
                return -1;

            keys.pop_back();
        }

        for (int i = 0; i < 1000; i++)
            llrb.remove(keys[i]);
            
        delete[] values;

        cout<<"Passed test " << test << endl;
    }

    cout<<"\t\nAll tests passed"<<endl;
    return 0;
}

int main()
{
    srand(time(NULL));
    try
    {
    if(test(10))
        cout<<"Test failed"<<endl;
    } catch (std::exception& e)
    {
        cout << e.what() << endl;
    }

    return 0;
}




