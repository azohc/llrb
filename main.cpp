#include "LLRBTree.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include <vector>
#include <unordered_map>

using std::cin;
using std::cout;
using std::endl;



int llrbtest(int max_elems)
{
    LLRBTree<int,int> llrb;
    std::unordered_map<int, bool> keymap;
    std::vector<int> keys;

    int* values = new int[max_elems];

    for (int i = 0; i < max_elems; i++)
    {
        int newkey = rand() % max_elems;

        //Comment these next two to ignore duplicate keys
        while(keymap.count(newkey))
            newkey = rand() % max_elems;

        keys.push_back(newkey);
        values[newkey] = rand() % INT_MAX;

        llrb.insert(newkey, values[newkey]);
        keymap.insert(std::pair<int,bool>(newkey, true));
    }


    while (!keys.empty())
    {
        int key = keys.back();
        if(llrb.get(key)!=values[key])
            return -1;

        keys.pop_back();
    }

    for (int i = 0; i < max_elems; i++)
        llrb.remove(keys[i]);
        
    delete[] values;
    
    return 0;
}

int main()
{
    srand(time(NULL));
    int num_tests = 50, max_elems = 3000;
    try
    {
    
        for(int test = 1; test <= num_tests; test++)
        {
            if(llrbtest(max_elems))
                cout << "Failed test " << test;
            // else
            //     cout << "Passed test " << test;
            
            // cout << "/" << num_tests << endl; 
        }

    } catch (std::exception& e)
    {
        cout << e.what() << endl;
    }


    // cout << endl << "All tests passed" << endl;
    return 0;
}




