#include <list>
#include <iostream>
using namespace std;
int main()
{
    list<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    for (list<int>::iterator itor = l.begin();
         itor != l.end();
         itor++)
    {
        cout << *itor << endl;
    }
}