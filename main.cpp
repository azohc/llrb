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


void opt_stresstest()
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

LLRBTree<int,char> opt_readtree()
{
    char* path;
    cout << "enter a file path, 'test_trees/test1.txt', for example (don't include apostrophes!)." << endl
        << "file path: ";
    cin >> path;

    return readtree<int,char>(path);
}

void opt_help()
{
    cout << "1. -> stress test" << endl
        << "\t perform X tests of Y insertions, searches and deletions." << endl
        << "\t you must enter X and Y, and the option to print the output of tests." << endl << endl

        << "2. -> read tree from file" << endl
        << "\t load a tree from a text file. there are files containing trees in the folder test_trees." << endl
        << "\t you must provide the path to a file that has a format similar to the test_trees files." << endl << endl

        << "3. -> test insertion" << endl
        << "\t measure the execution time of insert operation by inserting key value pairs into a tree." << endl << endl

        << "4. -> test search" << endl
        << "\t measure the execution time of search operation by getting key value pairs from a tree." << endl << endl

        << "5. -> test deletion" << endl
        << "\t measure the execution time of delete operation by deleting key value pairs from a tree." << endl << endl

        << "6. -> print help" << endl
        << "\t print this message." << endl << endl;
}

void printmenu(){
    cout << endl << "left leaning red black tree test menu" << endl 
        << "\t1. \t->\t stress test" << endl
        << "\t2. \t->\t read tree from file" << endl
        << "\t3. \t->\t test insertion" << endl
        << "\t4. \t->\t test search" << endl
        << "\t5. \t->\t test deletion" << endl
        << "\t6 \t->\t print help" << endl
        << "\t0. \t->\t exit" << endl;
}
int getchoice(){
    int choice = -1;

    cout << "enter your option: ";
    cin >> choice;
    while(choice < 0 || choice > 6)
    {
        cout << "enter your option (0 to 6): ";
        cin >> choice;
    }
    cout << endl;
    return choice;
}


int main()
{
    printmenu();
    int choice = getchoice();
    LLRBTree<int,char> tree;
    while(choice)
    {
        switch(choice)
        {
            case 1:
                opt_stresstest();
                break;
            case 2:
                tree = opt_readtree();
                break;
            case 3:
                //make tree 
                
                //test insertions

                break;
            case 4:
                //if no tree to insert into (make isempty func (llrb)) -> gen tree 
                
                //test searches

                break;
            case 5:
                //if no tree to delete from, make tree to delete from

                //test deletion

                break;

                //maybe add case to print tree
            case 6: 
                opt_help();
                break;
        }
        if(choice != 6)
            printmenu();
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




