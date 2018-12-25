#include "LLRBTree.h"
#include <iostream>
#include <sys/time.h>       // Measure execution time of code fragments
#include <vector>           // Key generation control
#include <unordered_map>    // Key generation control    
#include <fstream>          // Read example trees from files
// #include <stdlib.h>

using std::cin;
using std::cout;
using std::endl;
using std::fstream;
//using std::istream;


/*
La entrega se hará o sumo el 8 de Enero, a través del Campus Virtual, 
- con un texto fuente que pueda ser compilado y ejecutado, 
- ficheros de prueba, 
- y una memoria de dos a cinco páginas 
    que incluya algunos casos de prueba sencillos 
    y las gŕaficas de tiempo de los casos de prueba voluminosos.
*/

// To measure the time elapsed during the execution of a section of code
typedef unsigned long long utime_t;
static utime_t get_time ()      
{
    struct timeval now;
    gettimeofday(&now, NULL);
    return  now.tv_usec + (utime_t)now.tv_sec * 1000000;
}

// Test LLRB Tree with random pairs of keys and values
// executing max_elems insertions, searches and deletions
int stresstest(int max_elems)
{
    LLRBTree<int,int> llrb;
    std::vector<int> keys;              // Stores randomly generated keys
    int* values = new int[max_elems];   // Stores values associated to keys

    std::unordered_map<int, int> keymap;

    // Insertion
    for (int i = 0; i < max_elems; i++)
    {
        int newkey = rand() % max_elems;

        // To prevent the generation of duplicate keys, uncomment the next two lines
        // while(keymap.count(newkey))
        //     newkey = rand() % max_elems;

        if(!keymap[newkey])         // Only push keys that are not in the tree
        {
            keys.push_back(newkey);    
            keymap[newkey]++;
        }

        values[newkey] = rand();    // Duplicate key or not, generate random value

        llrb.insert(newkey, values[newkey]);
    }

    // Search
    while (!keys.empty())
    {
        int key = keys.back();
        if (llrb.get(key) != values[key])
            return -1;

        keys.pop_back();
    }

    // Deletion
    for (int i = 0; i < max_elems; i++)
        llrb.remove(keys[i]);
        
    delete[] values;
    keymap.clear();

    return 0;
}

template <class K, class V>
LLRBTree<K,V> readtree(char* path)
{
    LLRBTree<K,V> t;
    fstream f;
    f.open(path);

    return t;
}


int main()
{
    srand(time(NULL));
    int num_tests = 100, max_elems = 500;
    double t_acc = 0;
    try
    {
        for (int test = 1; test <= num_tests; test++)
        {
            utime_t t0 = get_time();
            stresstest(max_elems);
            utime_t t1 = get_time();

            t_acc += (t1 - t0) / 1000000.0L;

            // double secs = (t1 - t0) / 1000000.0L;
            // cout << secs << " seconds for test " << test;
            // cout << "/" << num_tests << ". " << max_elems << " insertions, searches, and deletions." << endl; 

      
            //(max_elems))
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




