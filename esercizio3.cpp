#include <iostream>
#include <string>
#include <list>

using namespace std;

int main() { setlocale(LC_ALL, "it_IT.UTF-8");
    
    list<int> numeri = {10, 20, 30, 40, 50};

    numeri.push_front(5);
    numeri.push_back(60);

    list<int>::iterator it;

    for(it = numeri.begin(); it != numeri.end(); ++it)
    {
        cout << *it << endl;
    }

    cout << endl;

    numeri.remove(30);

    it = numeri.begin();
    
    while(it != numeri.end() && *it != 40)
    {
        ++it;
    }

    if(it != numeri.end())
    {
        numeri.insert(it, 25);
    }

    numeri.pop_front();
    numeri.pop_back();

    for(auto it = numeri.begin(); it != numeri.end();  ++it)
    {
        cout << *it << endl;
    }

    cout << endl;

    cout << "Numeri nella lista: " << numeri.size() << endl;

    return 0;
}