//Mini progetto software per negozio di elettronica
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Prodotti 
{
    private:
        string codice;
        string nome;
        string categoria;
        double prezzo;
        static int prodottiAttivi;
    protected:
        void stampaDatiComuni() const
        {
            cout << "Codice: " << codice << endl;
            cout << "Nome: " << nome << endl;
            cout << "Categoria: " << categoria << endl;
            cout << "Prezzo: " << prezzo << endl;
        }
    public:
        Prodotti(string c, string n, string cat, double p) : codice(c), nome(n), categoria(cat), prezzo(p) 
        {
            prodottiAttivi++;
        }

        virtual ~Prodotti()
        {
            prodottiAttivi--;
        }

        const string& getCodice() const {return codice;}
        const string& getNome() const {return nome;}
        const string& getCategoria() const {return categoria;}
        double getPrezzo() const {return prezzo;}

        virtual void stampaDettagli() const = 0;

        bool operator==(const Prodotti& other) const
        {
            return codice == other.codice;
        }

        static int getProdottiAttivi() {return prodottiAttivi;}

        Prodotti(const Prodotti&) = delete;

        Prodotti& operator=(const Prodotti&) = delete;
};

int Prodotti::prodottiAttivi = 0;

class Smartphone : public Prodotti
{
    private:
        int memoriaGB;
    public:
        Smartphone(string c, string n, string cat, double p, int m) : Prodotti(c, n, cat, p), memoriaGB(m) {}

        void stampaDettagli() const override
        {
            Prodotti::stampaDatiComuni();
            cout << "Memoria: " << memoriaGB << " GB" << endl;
        }
};

class Computer : public Prodotti
{
    private:
        int ramGB;
    public:
        Computer(string c, string n, string cat, double p, int r) : Prodotti (c, n, cat, p), ramGB(r) {}

        void stampaDettagli() const override
        {
            Prodotti::stampaDatiComuni();
            cout << "RAM: " << ramGB << " GB" << endl;
        }
};

class Negozio
{
    private:
        vector<Prodotti*> catalogo;
    public:
        ~Negozio()
        {
            for (Prodotti* prodotto : catalogo)
            {
                delete prodotto;
            }
        }

        Negozio (const Negozio&) = delete;

        Negozio& operator=(const Negozio&) = delete;
};

int main() { setlocale(LC_ALL, "it_IT.UTF-8");

    cout << "Prodotti attivi: " << Prodotti::getProdottiAttivi() << endl << endl;

    {
        Smartphone s1 ("S001", "iPhone 15", "Smartphone", 999.99, 128);
        Computer c1 ("C001", "MacBook Pro", "Computer", 1999.99, 16);

        s1.stampaDettagli();
        cout << endl;

        c1.stampaDettagli();
        cout << endl;

        cout << "Prodotti attivi: " << Prodotti::getProdottiAttivi() << endl << endl;
    }

    cout << "Prodotti attivi: " << Prodotti::getProdottiAttivi() << endl << endl;

    return 0;
}