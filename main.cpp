#include "LLRBTree.h"
#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>

#include <vector>
#include <unordered_map>

using std::cin;
using std::cout;
using std::endl;


typedef unsigned long long utime_t;
static utime_t get_time ()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    return  now.tv_usec + (utime_t)now.tv_sec * 1000000;
}


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
        values[newkey] = rand();

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
    int num_tests = 10, max_elems = 2500;
    double t_acc = 0;
    try
    {
    
        for(int test = 1; test <= num_tests; test++)
        {
            utime_t t0 = get_time();
            llrbtest(max_elems);
            utime_t t1 = get_time();

            t_acc += (t1 - t0) / 1000000.0L;

            // double secs = (t1 - t0) / 1000000.0L;
            // cout << secs << " seconds for test " << test;
            // cout << "/" << num_tests << ". " << max_elems << " insertions, searches, and deletions." << endl; 

      
            // if(llrbtest(max_elems))
            //     cout << "Failed test " << test;
            // else
            //     cout << "Passed test " << test;
            // cout << "/" << num_tests <<  endl; 
        }

    } catch (std::exception& e)
    {
        cout << e.what() << endl;
    }

    cout << endl << "All tests passed." << endl;

    cout << "Seconds elapsed for " << num_tests << " tests of " << max_elems 
        << " insertions, searches and deletions: " << t_acc << " s." << endl;
    
    cout << "Average time per test: " << t_acc/num_tests << " s." << endl;

    return 0;
}




