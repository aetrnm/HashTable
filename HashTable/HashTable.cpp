#include <iostream>
#include <typeinfo>

using namespace std;

class HashTable
{
    const static int tableSize = 1000;

    string table[tableSize] = { "" };

public:

    //Constructor
    HashTable()
    {
        for (int i = 0; i < 1000; i++)
        {
            table[i] = "";
        }
    }

    void add(string s)
    {
        int hashCode = hash<string>()(s)%tableSize;
        table[hashCode] = s;
    }

    bool find(string s)
    {
        int hashCode = hash<string>()(s) % tableSize;
        if (table[hashCode] != "")
        {
            return true;
        }
        return false;
    }

    void remove(string s)
    {
        int hashCode = hash<string>()(s) % tableSize;
        if (table[hashCode] != "")
        {
            table[hashCode] = "";
        }
    }

};

int main()
{
    HashTable table = HashTable();
    table.add("qwerty");
    cout << table.find("qwety") << endl;
}