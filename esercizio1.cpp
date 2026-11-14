// Corso C++
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <set>

using namespace std;

int main() { setlocale(LC_ALL, "it_IT.UTF-8");

    set<int> numeri;

    numeri.insert(10);
    numeri.insert(5);
    numeri.insert(20);
    numeri.insert(10);
    numeri.insert(15);
    numeri.insert(5);
    numeri.insert(30);

    cout << "Gli elementi inseriti nel set sono: " << endl;

    for (const auto& numero : numeri) {
        cout << numero << endl;
    }

    cout << endl;

    if (numeri.find(15) != numeri.end()) {
        cout << "Il numero 15 è presente nel set." << endl;
    } else {
        cout << "Il numero 15 non è presente nel set." << endl;
    }

    cout << endl;

    if (numeri.find(100) != numeri.end()) {
        cout << "Il numero 100 è presente nel set." << endl;
    } else {
        cout << "Il numero 100 non è presente nel set." << endl;
    }

    cout << endl;

    numeri.erase(20);

    cout << "Elementi rimasti: " << numeri.size() << endl;

    cout << endl;

    cout << "Gli elementi nel set dopo erase() sono: " << endl;

    for (const auto& numero : numeri) {
        cout << numero << endl;
    }

    cout << endl;

    return 0;
}