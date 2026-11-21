//Mini progetto software per negozio di elettronica
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <clocale>
#include <map>

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
        map<string, int> giacenze;
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
            catalogo.erase(it);
            giacenze.erase(codiceDaRimuovere);
            delete prodottoDaRimuovere;
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
            }

            for (const auto& [codice, quantita] : giacenze)
            {
                cout << codice << ": " << quantita << endl;
            }

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

        negozio1.modificaGiacenza("C009", 20);

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

        negozio1.modificaGiacenza("S003", 5);

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

        negozio1.modificaGiacenza("C002", -5);

        negozio1.modificaGiacenza("X002", 10);

        cout << endl;

        int quantita1 = negozio1.getGiacenza("S003");
        if(quantita1 == -1)
        {
            cout << "Prodotto non presente" << endl;
        }
        else
        {
            cout << "Pezzi disponibili: " << quantita1 << endl;
        }

        int quantita2 = negozio1.getGiacenza("C009");
        if(quantita2 == -1)
        {
            cout << "Prodotto non presente" << endl;
        }
        else
        {
            cout << "Pezzi disponibili: " << quantita2 << endl;
        }        
        
        int quantita3 = negozio1.getGiacenza("C002");
        if(quantita3 == -1)
        {
            cout << "Prodotto non presente" << endl;
        }
        else
        {
            cout << "Pezzi disponibili: " << quantita3 << endl;
        }        
        
        int quantita4 = negozio1.getGiacenza("X002");
        if(quantita4 == -1)
        {
            cout << "Prodotto non presente" << endl;
        }
        else
        {
            cout << "Pezzi disponibili: " << quantita4 << endl;
        }
        cout << endl;
        
        negozio1.visualizzaGiacenze();

        negozio1.rimuoviProdotto("S003");
        int quantita5 = negozio1.getGiacenza("S003");
        if(quantita5 == -1)
        {
            cout << "Prodotto non presente" << endl;
        }
        else
        {
            cout << "Pezzi disponibili: " << quantita5 << endl;
        }

        cout << "Prodotti attivi: " << Prodotti::getProdottiAttivi() << endl << endl;
    }

    cout << "Prodotti attivi: " << Prodotti::getProdottiAttivi() << endl << endl;

    return 0;
}