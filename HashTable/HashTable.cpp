#include <iostream>
#include <typeinfo>

using namespace std;

int filledCells = 0;

class HashTable
{
    static const int primeNumbersList[7];
    int tableSize;
    string* table;
    hash<string> hasher = hash<string>();

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
            if (oldTable[i] != "") 
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
        //delete[] table;
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
            if (table[hash] != "" && table[hash] == s)
            {
                return true;
            }
            else if (table[hash] == "") 
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
            if (table[hash] != "" && table[hash] == s) 
            {
                table[hash] = "";
            }
            else if (table[hash] == "") 
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
    //table.printTable();
    int start = clock();
    table.add("cat");
    //table.printTable();
    table.add("dog");
    //table.printTable();
    table.add("horse");
    //table.printTable();
    table.add("cat");
    //table.printTable();
    int finish = clock();
    cout << "Time spent: " << finish - start << endl;
    try 
    {
        table.remove("ashsa");
    }
    catch (const exception& e)
    {
        cout << "Error: " << e.what() << endl;
    }
    cout << table.find("dog") << endl;
    cout << table.find("dolphin") << endl;

}
