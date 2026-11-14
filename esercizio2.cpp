#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

int main() { setlocale(LC_ALL, "it_IT.UTF-8");

    map<string, int> voti;

    voti["Mario"] = 28;
    voti["Luca"] = 30;
    voti["Giulia"] = 25;

    voti.insert({"Giuseppe", 27});
    voti.insert({"Francesca", 23});

    cout << "Gli studenti e i loro voti sono: " << endl;

    for (const auto& [nome, voto] : voti) {
        cout << nome << ": " << voto << endl;
    }

    cout << endl;

    auto it = voti.find("Luca");
    if (it != voti.end()) 
    {
        cout << "Studente " << it->first << " trovato." << endl;
        cout << "Voto: " << it->second << endl;
    }
    else
    {
        cout << "Studente non trovato." << endl;
    }

    cout << endl;

    voti["Mario"] = 18;

    voti.erase("Giuseppe");

    cout << endl;

    cout << "Gli studenti e i loro voti dopo le modifiche sono: " << endl;

    for (const auto& [nome, voto] : voti) {
        cout << nome << ": " << voto << endl;
    }

    return 0;

}