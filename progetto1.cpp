//Mini progetto software per negozio di elettronica
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <clocale>

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

        void setCodice(const string& c) {codice = c;}
        void setNome(const string& n) {nome = n;}
        void setCategoria(const string& cat) {categoria = cat;}
        bool setPrezzo(double p)
        {
            if (p <= 0)
            {
                return false;
            }
            prezzo = p;
            return true;
        }
        
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
        Negozio() = default;

        ~Negozio()
        {
            for (Prodotti* prodotto : catalogo)
            {
                delete prodotto;
            }
        }

        Negozio (const Negozio&) = delete;

        Negozio& operator=(const Negozio&) = delete;

        const Prodotti* cercaProdotto(const string& codice) const
        {
            auto it = find_if(catalogo.begin(), catalogo.end(), [&codice](const Prodotti* prodotto)
            {
                return prodotto != nullptr && prodotto->getCodice() == codice;
            });

            return it != catalogo.end() ? *it : nullptr;
        }

        bool aggiungiProdotto(Prodotti* nuovoProdotto)
        {
            if (nuovoProdotto == nullptr)
            {
                return false;
            }

            if (cercaProdotto(nuovoProdotto->getCodice()) != nullptr)
            {
                return false;
            }

            catalogo.push_back(nuovoProdotto);
            return true;
        }

        void visualizzaCatalogo() const
        {
            if (catalogo.empty())
            {
                cout << "Il catalogo è vuoto." << endl;
                cout << "Prodotti attivi: " << Prodotti::getProdottiAttivi() << endl;
                return;
            }

            for (const Prodotti* prodotto : catalogo)
            {
                prodotto->stampaDettagli();
                cout << endl;
            }
        }

        Prodotti* cercaProdotto(const string& codice)
        {
            auto it = find_if(catalogo.begin(), catalogo.end(), [&codice](Prodotti* prodotto)
            {
                return prodotto != nullptr && prodotto->getCodice() == codice;
            });
            return it != catalogo.end() ? *it : nullptr;
        }

        bool modificaPrezzo(const string& codice, double nuovoPrezzo)
        {
            Prodotti* prodotto = cercaProdotto(codice);
            if (prodotto == nullptr)
            {
                return false;
            }
            return prodotto->setPrezzo(nuovoPrezzo);
        }
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

    {
        cout << "Prodotti attvi: " << Prodotti::getProdottiAttivi() << endl << endl;

        Negozio negozio1;

        Prodotti* p1 = new Smartphone("S002", "Samsung Galaxy s23", "Smartphone", 899.99, 256);
        if(negozio1.aggiungiProdotto(p1))
        {
            cout << "Prodotto aggiunto con successo." << endl;
        }
        else
        {
            cout << "Errore nell'aggiunta del prodotto." << endl;
            delete p1;
        }

        Prodotti* p2 = new Computer("C002", "Dell XPS 13", "Computer", 1499.99, 16);
        if(negozio1.aggiungiProdotto(p2))
        {
            cout << "Prodotto aggiunto con successo." << endl;
        }
        else
        {
            cout << "Errore nell'aggiunta del prodotto." << endl;
            delete p2;
        }

        Prodotti* p3 = new Smartphone("S003", "Google Pixel 8", "Smartphone", 799.99, 128);
        if(negozio1.aggiungiProdotto(p3))
        {
            cout << "Prodotto aggiunto con successo." << endl;
        }
        else
        {
            cout << "Errore nell'aggiunta del prodotto." << endl;
            delete p3;
        }

        Prodotti* p4 = new Computer("C003", "HP Spectre x360", "Computer", 1299.99, 16);
        if(negozio1.aggiungiProdotto(p4))
        {
            cout << "Prodotto aggiunto con successo." << endl;
        }
        else
        {
            cout << "Errore nell'aggiunta del prodotto." << endl;
            delete p4;
        }

        Prodotti* p5 = new Smartphone("S004", "OnePlus 11", "Smartphone", 699.99, 256);
        if(negozio1.aggiungiProdotto(p5))
        {
            cout << "Prodotto aggiunto con successo." << endl;
        }
        else
        {
            cout << "Errore nell'aggiunta del prodotto." << endl;
            delete p5;
        }

        Prodotti* p6 = new Computer("C004", "Lenovo ThinkPad X1", "Computer", 1599.99, 32);
        if(negozio1.aggiungiProdotto(p6))
        {
            cout << "Prodotto aggiunto con successo." << endl;
        }
        else
        {
            cout << "Errore nell'aggiunta del prodotto." << endl;
            delete p6;
        }

        Prodotti* p7 = new Smartphone("S005", "Sony Xperia 1 IV", "Smartphone", 999.99, 512);
        if(negozio1.aggiungiProdotto(p7))
        {
            cout << "Prodotto aggiunto con successo." << endl;
        }
        else
        {
            cout << "Errore nell'aggiunta del prodotto." << endl;
            delete p7;
        }

        Prodotti* p8 = new Computer("C005", "Asus ROG Zephyrus G14", "Computer", 1799.99, 16);
        if(negozio1.aggiungiProdotto(p8))
        {
            cout << "Prodotto aggiunto con successo." << endl;
        }
        else
        {
            cout << "Errore nell'aggiunta del prodotto." << endl;
            delete p8;
        }

        Prodotti* p9 = new Smartphone("S006", "Xiaomi Mi 13", "Smartphone", 599.99, 128);
        if(negozio1.aggiungiProdotto(p9))
        {
            cout << "Prodotto aggiunto con successo." << endl;
        }
        else
        {
            cout << "Errore nell'aggiunta del prodotto." << endl;
            delete p9;
        }

        Prodotti* p10 = new Computer("C006", "Acer Swift 3", "Computer", 899.99, 8);
        if(negozio1.aggiungiProdotto(p10))
        {
            cout << "Prodotto aggiunto con successo." << endl;
        }
        else
        {
            cout << "Errore nell'aggiunta del prodotto." << endl;
            delete p10;
        }

        negozio1.visualizzaCatalogo();
        cout << endl;

        cout << "Prodotti attivi: " << Prodotti::getProdottiAttivi() << endl << endl;

        const Prodotti* trovato1 = negozio1.cercaProdotto("S003");
        if (trovato1 != nullptr)
        {
            cout << "Prodotto trovato: " << trovato1->getNome() << endl;
        }
        else
        {
            cout << "Prodotto non trovato." << endl;
        }
        cout << endl;

        const Prodotti* trovato2 = negozio1.cercaProdotto("X002");
        if (trovato2 != nullptr)
        {
            cout << "Prodotto trovato: " << trovato2->getNome() << endl;
        }
        else
        {
            cout << "Prodotto non trovato." << endl;
        }
        cout << endl;

        Prodotti* p11 = new Smartphone("S002", "Samsung Galaxy s23", "Smartphone", 899.99, 256);
        if(negozio1.aggiungiProdotto(p11))
        {
            cout << "Prodotto aggiunto con successo." << endl;
        }
        else
        {
            cout << "Errore nell'aggiunta del prodotto: codice duplicato." << endl;
            delete p11;
        }

        if (!negozio1.aggiungiProdotto(nullptr))
        {
            cout << "Errore nell'aggiunta del prodotto: puntatore nullo." << endl;
        }

        if (negozio1.modificaPrezzo("C002", 0))
        {
            cout << "Prezzo modificato con successo." << endl;
        }
        else
        {
            cout << "Errore nella modifica del prezzo: prezzo non valido." << endl;
        }
        cout << endl;

        negozio1.modificaPrezzo("C002", 1399.99);
        cout << endl;

        negozio1.modificaPrezzo("X002", 1299.99);
        cout << endl;

        negozio1.modificaPrezzo("C003", -230.50);
        cout << endl;

        cout << "Prodotti attivi: " << Prodotti::getProdottiAttivi() << endl << endl;
    }

    cout << "Prodotti attivi: " << Prodotti::getProdottiAttivi() << endl << endl;

    return 0;
}