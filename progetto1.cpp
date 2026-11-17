//Mini progetto software per negozio di elettronica
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <set>

using namespace std;

class Prodotti 
{
    private:
        string codice;
        string nome;
        string categoria;
        double prezzo;
        int static prodottiAttivi;
    public:
        Prodotti(string c, string n, string cat, double p) : codice(c), nome(n), categoria(cat), prezzo(p) 
        {
            prodottiAttivi++;
        }

        virtual ~Prodotti() = default;

        const string& getCodice() const {return codice;}
        const string& getNome() const {return nome;}
        const string& getCategoria() const {return categoria;}
        double getPrezzo() const {return prezzo;}

        virtual void stampaDettagli() const
        {
            cout << "Codice: " << codice << endl;
            cout << "Nome: " << nome << endl;
            cout << "Categoria: " << categoria << endl;
            cout << "Prezzo: " << prezzo << endl;
        }
};


int main() { setlocale(LC_ALL, "it_IT.UTF-8");


}