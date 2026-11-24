//Mini progetto software per negozio di elettronica
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <clocale>
#include <map>
#include <set>

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

        void setNome(const string& n) {nome = n;}
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
        map<string, int> giacenze;
        set<string> categorie;
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

        bool aggiungiProdotto(Prodotti* nuovoProdotto, int quantitaIniziale = 0)
        {
            if (nuovoProdotto == nullptr)
            {
                return false;
            }

            if (cercaProdotto(nuovoProdotto->getCodice()) != nullptr)
            {
                return false;
            }     

            if (quantitaIniziale < 0)
            {
                return false;
            }

            catalogo.push_back(nuovoProdotto);
            
            giacenze[nuovoProdotto->getCodice()] = quantitaIniziale;

            categorie.insert(nuovoProdotto->getCategoria());

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

        bool rimuoviProdotto(const string& codice)
        {
            auto it = find_if(catalogo.begin(), catalogo.end(), [&codice](Prodotti* prodotto)
            {
                return prodotto != nullptr && prodotto->getCodice() == codice;
            });

            if (it == catalogo.end())
            {
                return false;
            }

            Prodotti* prodottoDaRimuovere = *it;

            string codiceDaRimuovere = prodottoDaRimuovere->getCodice();
            
            string categoriaDaRimuovere = prodottoDaRimuovere->getCategoria();

            catalogo.erase(it);
            
            giacenze.erase(codiceDaRimuovere);
            
            delete prodottoDaRimuovere;

            auto itCategoria = find_if(catalogo.begin(), catalogo.end(), [&categoriaDaRimuovere] (const Prodotti* prodotto)
                {
                    return prodotto != nullptr && prodotto->getCategoria() == categoriaDaRimuovere;
                }
            );

            if (itCategoria == catalogo.end())
            {
                categorie.erase(categoriaDaRimuovere);
            }
            
            return true;
        }

        bool modificaGiacenza(const string& codice, int nuovaQuantita)
        {
            if (nuovaQuantita < 0)
            {
                cout << "Errore, quantità inserita errata" << endl;
                return false;
            }

            auto it = giacenze.find(codice);

            if (it == giacenze.end())
            {
                return false;
            }

            it->second = nuovaQuantita;

            cout << "Giacenza prodotto " << it->first << " modificata correttamente!" << endl;
            cout << "Nuova giacenza: " << it->second << endl;
            
            return true;
        }

        int getGiacenza(const string& codice) const
        {
            auto it = giacenze.find(codice);

            if (it == giacenze.end())
            {
                return -1;
            }

            return it->second;
        }

        void visualizzaGiacenze() const
        {
            if (giacenze.empty())
            {
                cout << "Catalogo vuoto!" << endl;
                return;
            }

            for (const auto& [codice, quantita] : giacenze)
            {
                cout << codice << ": " << quantita << endl;
            }
        }

        void visualizzaCategorie() const
        {
            if (categorie.empty())
            {
                cout << "Nessuna categoria disponibile." << endl;
                return;
            }

            for (const string& categoria : categorie)
            {
                cout << categoria << endl;
            }
        }

        bool categoriaPresente(const string& categoria) const
        {
            auto it = categorie.find(categoria);

            if (it == categorie.end())
            {
                return false;
            }

            return true;
        }
};

int main() { setlocale(LC_ALL, "it_IT.UTF-8");

    cout << "Prodotti attivi: " << Prodotti::getProdottiAttivi() << endl << endl;

    {
        cout << "Prodotti attvi: " << Prodotti::getProdottiAttivi() << endl << endl;

        Negozio negozio1;
        
        Prodotti* p12 = new Computer("C009", "ASUS Vivobook", "Computer", 979.99, 16);
        if(negozio1.aggiungiProdotto(p12, 15))
        {
            cout << "Prodotto aggiunto con successo." << endl;
        }
        else
        {
            cout << "Errore nell'aggiunta del prodotto" << endl;
            delete p12;
        }

        Prodotti* p13 = new Smartphone("S003", "iPhone 15", "Smartphone", 500.00, 128);
        if(negozio1.aggiungiProdotto(p13, 0))
        {
            cout << "Prodotto aggiunto con successo." << endl;
        }
        else
        {
            cout << "Errore nell'aggiunta del prodotto" << endl;
            delete p13;
        }

        Prodotti* p14 = new Computer("C002", "MacBook 5", "Computer", 1200.00, 16);
        if(negozio1.aggiungiProdotto(p14, 10))
        {
            cout << "Prodotto aggiunto con successo." << endl;
        }
        else
        {
            cout << "Errore nell'aggiunta del prodotto" << endl;
            delete p14;
        }

        negozio1.visualizzaCategorie();

        if (negozio1.categoriaPresente("Smartphone"))
        {
            cout << "Categoria trovata!" << endl;
        }
        else
        {
            cout << "Categoria non travata!" << endl;
        }

        if (negozio1.categoriaPresente("Tablet"))
        {
            cout << "Categoria trovata!" << endl;
        }
        else
        {
            cout << "Categoria non trovata!" << endl;
        }

        if (negozio1.rimuoviProdotto("C009"))
        {
            cout << "Prodotto eliminato con successo!" << endl;
        }
        else
        {
            cout << "Errore nella eliminazione del prodotto" << endl;
        }

        if (negozio1.rimuoviProdotto("C002"))
        {
            cout << "Prodotto eliminato con successo!" << endl;
        }
        else
        {
            cout << "Errore nella eliminazione del prodotto" << endl;
        }

        negozio1.visualizzaCategorie();

        cout << "Prodotti attivi: " << Prodotti::getProdottiAttivi() << endl << endl;
    }

    cout << "Prodotti attivi: " << Prodotti::getProdottiAttivi() << endl << endl;

    return 0;
}