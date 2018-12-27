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
using std::istream;


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
// executing max_elems insertions, searches and deletions num_tests times
int stresstest(int num_tests, int max_elems, bool verbose)
{
    srand(time(NULL));
    double t_acc = 0;   // Accumulates time elapsed in executing a test loop
    
    LLRBTree<int,int> llrb;
    std::vector<int> keys;                  // Stores randomly generated keys
    std::unordered_map<int, int> keymap;    // Stores keys to ensure that every key in keys vector is unique

    try
    {
        for (int test = 1; test <= num_tests; test++)
        {
            int* values = new int[max_elems];       // Stores values associated to keys

            utime_t t0 = get_time();

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
            
            utime_t t1 = get_time();

            delete[] values;
            keymap.clear();
    
            t_acc += ((t1 - t0) / 1000000.0L);

            if(verbose)
            {
                cout << ((t1 - t0) / 1000000.0L) << " seconds elapsed for test " << test 
                    << "/" << num_tests << ". " << endl;  
            }
        }

    } catch (std::exception& e)
    {
        cout << e.what() << endl;
    }

    if(verbose)
    {
        cout << endl << "All tests passed." << endl;

        cout << "Seconds elapsed for " << num_tests << " tests of " << max_elems 
            << " insertions, searches and deletions: " << t_acc << " s." << endl;
        
        cout << "Average time per test: " << t_acc/num_tests << " s." << endl;
    }   

    return 0;
}

template <class K, class V>
LLRBTree<K,V> readtree(const char* path)
{
    LLRBTree<K,V> t;
    fstream f;
    f.open(path);

    if(f.is_open())
        cout << "Opened example tree " << path << "." << endl;
    else
    { 
        cout << "Failed to open file " << path << "." << endl 
            << "Returning empty tree..." << endl;
        return t;
    }

    return t;
}

int main()
{
    // stresstest(10, 500, true);    
    LLRBTree <int,char*> t_hh = readtree<int,char*>("test_trees/hiphop.txt");


    return 0;
}




