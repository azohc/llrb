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
using std::ifstream;
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

void opt_st()
{
    int n_tests, m_elems;
    char c;
    cout << endl << "maximum number of elements to test with: ";
    cin >> m_elems;
    while(m_elems < 1)
    {
        cout << "enter a positive number: ";
        cin >> m_elems;
    }
    
    cout << "number of tests to execute: ";
    cin >> n_tests;
    while(n_tests < 1)
    {
        cout << "enter a positive number: ";
        cin >> m_elems;
    }

    cout << "print output messages? (y/n): ";
    cin >> c;
    while(tolower(c) != 'y' && tolower(c) != 'n')
    {
        cout << "enter y for yes or n for no: ";
        cin >> c;
    }  


    stresstest(n_tests, m_elems, true);
}


template <class K, class V>
LLRBTree<K,V> readtree(const char* path)
{
    LLRBTree<int,char> t;
    ifstream f;
    f.open(path);

    if(f.is_open())
        cout << "Opened example tree " << path << "." << endl;
    else
    { 
        cout << "Failed to open file " << path << "." << endl 
            << "Returning empty tree..." << endl;
        return t;
    }

    K n;
    V c;
    while (!f.eof())
    {
        f >> n >> c;
        t.insert(n, c);
    }
    
    f.close();
    return t;
}

template <class K, class V>
void benchmark_insert(LLRBTree<K,V> &t, const std::vector<K> &keys, const std::vector<V> &vals)
{
    while(!keys.empty() && !vals.empty())
    {
        t.insert(keys.back(), vals.back());
        keys.pop_back();
        vals.pop_back();
    }
}

int getchoice(){
    int choice = -1;
    cout << "left leaning red black tree test menu" << endl 
        << "\t2. \t->\t stress test" << endl
        << "\t3. \t->\t read tree from file" << endl
        << "\t4. \t->\t test insertion" << endl
        << "\t5. \t->\t test search" << endl
        << "\t6. \t->\t test deletion" << endl
        << "\t1. \t->\t print help" << endl
        << "\t0. \t->\t exit" << endl;

    cout << "enter your option: ";
    cin >> choice;
    while(choice < 0 || choice > 6)
    {
        cout << "enter your option (0 to 6): ";
        cin >> choice;
    }
    return choice;
}


int main()
{
    int choice = getchoice();
    while(choice)
    {
        switch(choice)
        {
            case 1:

                break;
            case 2:
            
                opt_st();
                break;
            case 3:
            
                break;
            case 4:
            
                break;
            case 5:
            
                break;
            case 6: 

                break;
        }
        choice = getchoice();
    }

    return 0;
    
    /*-----------------
    stresstest(x, y, v)
        x loops of y insertions, searches and deletions in a tree.
        v (bool) verbose mode, enables/disables the printing of output messages 
    --------------*/
        


    //LLRBTree <int,char> t_hh = readtree<int,char>("test_trees/test1.txt");

    /*---------------
    
    --------------*/


    //fun to measure insertion time


    //fun to measure search time
    //fun to measure deletion time

}




