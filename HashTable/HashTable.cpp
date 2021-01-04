#include <iostream>
#include <typeinfo>
#include "windows.h"
#include <ctime>
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;

using namespace std;

class HashTable
{
    static const int primeNumbersList[7];
    int tableSize;
    string* table;
    hash<string> hasher = hash<string>();
    int filledCells = 0;

private:
    int currentSizeIndex = 0;

    void resize() 
    {
        string* oldTable = table;
        int oldTableSize = tableSize;
        currentSizeIndex++;
        tableSize = primeNumbersList[currentSizeIndex];
        table = new string[tableSize];
        rehash(oldTable, oldTableSize);
        delete[] oldTable;
    }

    void rehash(string* oldTable, int oldTableSize) 
    {
        for(int i = 0; i < oldTableSize; i++)
        {
            if (!oldTable[i].empty()) 
            {
                this->add(oldTable[i]);
            }
        }
    }

public:

    //Constructor
    HashTable()
    {
        tableSize = primeNumbersList[0];
        table = new string[tableSize];
        for (int i = 0; i < tableSize; i++)
        {
            table[i] = "";
        }
    }

    int hash1(string s) {
        return hasher(s) % tableSize;
    }

    int hash2(string s) {
        return hasher(s + "#") % tableSize;
    }
    
    void add(string s)
    {
        if (filledCells / tableSize * 100 >= 70) 
        {
            resize();
        }
        if (this->find(s)) //this - find будет вызван от объекта от которого вызывался add
        { 
            return;
        }
        for (int i = 0; true; i++) 
        {
            int hash = (hash1(s) + i*hash2(s))%tableSize;
            if (table[hash] == "") 
            {
                table[hash] = s;
                filledCells++;
                break;
            }
        }
    }

    bool find(string s)
    {
        for (int i = 0; true; i++) 
        {
            int hash = (hash1(s) + i * hash2(s)) % tableSize;
            if (!table[hash].empty() && table[hash] == s)
            {
                return true;
            }
            if (table[hash].empty()) 
            {
                return false;
            }
        }
    }

    void remove(string s)
    {
        for (int i = 0; true; i++) 
        {
            int hash = (hash1(s) + i * hash2(s)) % tableSize;
            if (!table[hash].empty() && table[hash] == s) 
            {
                table[hash] = "";
            }
            else if (table[hash].empty()) 
            {
                throw runtime_error("remove(): no such element");
            }
        }
    }

    void printTable() 
    {
        for (int i = 0; i < tableSize; i++) 
        {
            printf("{%d} ", i);
            cout << table[i] << endl;
        }
        cout << endl;
    }
};

const int HashTable::primeNumbersList[7] = { 11, 103, 1009, 10007, 100003, 1000003, 10000019};

int main()
{
    HashTable table = HashTable();
	
    const auto t1 = Clock::now();
	
    table.add("cat");
    table.add("dog");
    table.add("horse");
    table.add("cat");
    const auto t2 = Clock::now();
	
    try 
    {
        table.remove("ashsa");
    }
    catch (const exception& e)
    {
        cout << "Error: " << e.what() << endl;
    }
	

    cout << "Time spent: " << chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()
        << " nanoseconds" << endl;
}
