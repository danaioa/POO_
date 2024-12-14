#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <memory>
#include <random>
#include <iomanip>
#include <stdexcept>
using namespace std;


class ProdusException : public std::exception {
protected:
    std::string mesaj;
public:
    explicit ProdusException(std::string  msg) : mesaj(std::move(msg)) {}
    [[nodiscard]] const char* what() const noexcept override {
        return mesaj.c_str();
    }
};


class FisierException : public ProdusException {
public:
    explicit FisierException(const std::string& msg) : ProdusException(msg) {}
};


class ProdusInvalidException : public ProdusException {
public:
    explicit ProdusInvalidException(const std::string& msg) : ProdusException(msg) {}
};


class Produs {
protected:
    string nume;
    int calorii;
    vector<string> ingrediente;
    bool vegan;
    int pret;
    int gramaj;

public:
    Produs(string nume, int calorii, const vector<string>& ingrediente, bool vegan, int pret, int gramaj)
       : nume(std::move(nume)), calorii(calorii), ingrediente(ingrediente), vegan(vegan), pret(pret), gramaj(gramaj) {

        if (pret <= 0 || gramaj <= 0) {
            throw ProdusInvalidException("Pretul si gramajul produsului trebuie sa fie pozitive.");
        }
    }

    virtual void afisare(int index) const {
        cout << "Ordin#" << index << "# " << nume << ", " << calorii << " kcal, "
            << (vegan ? "vegan" : "non-vegan") << ", Pret: " << pret << " lei, "
            << "Gramaj: " << gramaj << " g\n        Ingrediente: ";
        for (const auto& ing : ingrediente) cout << ing << " ";
        cout << endl;
    }

    [[nodiscard]] virtual unique_ptr<Produs> clone() const = 0;
    virtual ~Produs() = default;

    [[nodiscard]] int getPret() const { return pret; }
    [[nodiscard]] string getNume() const { return nume; }
};


class Bautura : public Produs {
public:
    Bautura(const string& nume, int calorii, const vector<string>& ingrediente, bool vegan, int pret, int gramaj)
        : Produs(nume, calorii, ingrediente, vegan, pret, gramaj) {}

    void afisare(int index) const override {
        cout << "Ordin#" << index << "#  " << nume << ", " << calorii << " kcal, "
            << (vegan ? "vegan" : "non-vegan") << ", Pret: " << pret << " lei, "
            << "Gramaj: " << gramaj << " g\n        Ingrediente: ";
        for (const auto& ing : ingrediente) cout << ing << " ";
        cout << endl;
    }

    [[nodiscard]] unique_ptr<Produs> clone() const override {
        return make_unique<Bautura>(*this);
    }

    static unique_ptr<Bautura> dinFisier(const string& linie) {
        stringstream ss(linie);
        string nume, ingredienteStr, veganStr;
        int calorii, pret, gramaj;
        vector<string> ingrediente;
        bool vegan;

        getline(ss, nume, ',');
        ss >> pret;
        ss.ignore();
        ss >> gramaj;
        ss.ignore();
        ss >> calorii;
        ss.ignore();
        getline(ss, ingredienteStr, ',');
        stringstream ssIngrediente(ingredienteStr);
        string ing;
        while (getline(ssIngrediente, ing, ';')) {
            ingrediente.push_back(ing);
        }
        getline(ss, veganStr);
        vegan = (veganStr == "da");

        return make_unique<Bautura>(nume, calorii, ingrediente, vegan, pret, gramaj);
    }
};


class Desert : public Produs {
    int cantitate;

public:
    Desert(const string& nume, int calorii, const vector<string>& ingrediente, bool vegan, int pret, int gramaj, int cantitate)
        : Produs(nume, calorii, ingrediente, vegan, pret, gramaj), cantitate(cantitate) {}

    void afisare(int index) const override {
        cout << "Ordin# " << index << " # : " << nume << ", " << calorii << " kcal, "
            << (vegan ? "vegan" : "non-vegan") << ", Pret: " << pret << " lei, "
            << "Gramaj: " << gramaj << " g, Cantitate: " << cantitate << " g\n        Ingrediente: ";
        for (const auto& ing : ingrediente) cout << ing << " ";
        cout << endl;
    }

    [[nodiscard]] unique_ptr<Produs> clone() const override {
        return make_unique<Desert>(*this);
    }

    static unique_ptr<Desert> dinFisier(const string& linie) {
        stringstream ss(linie);
        string nume, ingredienteStr, veganStr;
        int calorii, pret, gramaj, cantitate;
        vector<string> ingrediente;
        bool vegan;

        getline(ss, nume, ',');
        ss >> pret;
        ss.ignore();
        ss >> gramaj;
        ss.ignore();
        ss >> calorii;
        ss.ignore();
        getline(ss, ingredienteStr, ',');
        stringstream ssIngrediente(ingredienteStr);
        string ing;
        while (getline(ssIngrediente, ing, ';')) {
            ingrediente.push_back(ing);
        }
        ss >> cantitate;
        ss.ignore();
        getline(ss, veganStr);
        vegan = (veganStr == "da");

        return make_unique<Desert>(nume, calorii, ingrediente, vegan, pret, gramaj, cantitate);
    }
};


class Preparat : public Produs {
    int timpPreparare;

public:
    Preparat(const string& nume, int calorii, const vector<string>& ingrediente, bool vegan, int pret, int gramaj, int timpPreparare)
        : Produs(nume, calorii, ingrediente, vegan, pret, gramaj), timpPreparare(timpPreparare) {}

    void afisare(int index) const override {
        cout << "Ordin# " << index << " # : " << nume << ", " << calorii << " kcal, "
            << (vegan ? "vegan" : "non-vegan") << ", Pret: " << pret << " lei, "
            << "Gramaj: " << gramaj << " g, Timp preparare: " << timpPreparare << " min\n         Ingrediente: ";
        for (const auto& ing : ingrediente) cout << ing << " ";
        cout << endl;
    }

    [[nodiscard]] unique_ptr<Produs> clone() const override {
        return make_unique<Preparat>(*this);
    }

    static unique_ptr<Preparat> dinFisier(const string& linie) {
        stringstream ss(linie);
        string nume, ingredienteStr, veganStr;
        int calorii, pret, gramaj, timpPreparare;
        vector<string> ingrediente;
        bool vegan;

        getline(ss, nume, ',');
        ss >> pret;
        ss.ignore();
        ss >> gramaj;
        ss.ignore();
        ss >> calorii;
        ss.ignore();
        getline(ss, ingredienteStr, ',');
        stringstream ssIngrediente(ingredienteStr);
        string ing;
        while (getline(ssIngrediente, ing, ';')) {
            ingrediente.push_back(ing);
        }
        ss >> timpPreparare;
        ss.ignore();
        getline(ss, veganStr);
        vegan = (veganStr == "da");

        return make_unique<Preparat>(nume, calorii, ingrediente, vegan, pret, gramaj, timpPreparare);
    }
};


class MeniuPrincipal {
    vector<unique_ptr<Produs>> produse;

public:

    void adaugaProdus(unique_ptr<Produs> produs) {
        produse.push_back(move(produs));
    }

    [[nodiscard]] const vector<unique_ptr<Produs>>& getProduse() const {
        return produse;
    }

    // Afișează meniul cu produse
    void afiseazaMeniu() const {
        int index = 1;
        for (const auto& produs : produse) {
            produs->afisare(index);
            ++index;
        }
    }

    // Returnează produsul selectat pe baza indexului
    unique_ptr<Produs> selecteazaProdus(int index) {
        if (index > 0 && index <= produse.size()) {
            return std::move(produse[index - 1]);
        }
        else {
            cout << "Index invalid!" << endl;
            return nullptr;
        }
    }

    [[nodiscard]] size_t getNrProduse() const {
        return produse.size();
    }

    // Citire produse din fișier
    void citesteProduseDinFisier(const string& numeFisier, bool esteBautura = false) {
        ifstream fisier(numeFisier);
        if (!fisier.is_open()) {
            cerr << "Eroare la deschiderea fisierului: " << numeFisier << endl;
            return;
        }

        string linie;
        while (getline(fisier, linie)) {
            if (linie.empty()) continue;

            if (esteBautura) {
                adaugaProdus(Bautura::dinFisier(linie));
            }
            else {
                adaugaProdus(Preparat::dinFisier(linie));
            }
        }
        fisier.close();
    }
};


template <typename T>
void citesteProduseDinFisier(const string& numeFisier, MeniuPrincipal& meniu) {
    ifstream fisier(numeFisier);
    if (!fisier.is_open()) {

        throw std::runtime_error("Eroare la deschiderea fisierului: " + numeFisier);
    }

    string linie;
    while (getline(fisier, linie)) {

        if (linie.empty()) continue;

        try {

            meniu.adaugaProdus(T::dinFisier(linie));
        } catch (const std::exception& e) {

            cout << "Eroare la citirea produsului din linia: " << linie << ". Detalii: " << e.what() << endl;
        }
    }

    fisier.close();
}

class Obiectiv {
public:
    virtual ~Obiectiv() = default;

    [[nodiscard]] virtual string getObiectivString() const = 0;


    [[nodiscard]] virtual int calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const = 0;
};



class Slabire : public Obiectiv {
public:
    [[nodiscard]] string getObiectivString() const override {
        return "Slabire";
    }

    [[nodiscard]] int calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const override {
        return static_cast<int>(std::round(10 * greutate + 6.25 * inaltime - 5 * varsta - 161));

    }
};


class MasaMusculara : public Obiectiv {
public:
    [[nodiscard]] string getObiectivString() const override {
        return "Crestere masa musculara";
    }

    [[nodiscard]] int calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const override {

        return static_cast<int>(10 * greutate + 6.25 * inaltime - 5 * varsta + 5);

    }
};


class Mentinere : public Obiectiv {
public:
    [[nodiscard]] string getObiectivString() const override {
        return "Mentinere";
    }

    [[nodiscard]] int calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const override {

        return static_cast<int>(10 * greutate + 6.25 * inaltime - 5 * varsta + 5);

    }
};




int citesteUltimulNumar(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "eroare la deschiderea fisierului!" << endl;
        return -1;  // returneaza un ID invalid in caz de eroare
    }

    string linie;
    int ultimul_id = 0;

    // citim linie cu linie
    while (getline(file, linie)) {
        // cautam linia care incepe cu "ID: "
        size_t pos = linie.find("ID: ");
        if (pos == 0) {  // linia incepe cu "ID: "
            try {
                // gasim ID-ul dupa "ID: "
                string id_str = linie.substr(4);
                int id = stoi(id_str);  // extragem ID-ul
                ultimul_id = id;  // actualizam ultimul ID
            }
            catch (const exception& e) {
                cerr << "eroare la citirea ID-ului: " << e.what() << endl;
            }
        }
    }

    file.close();
    return ultimul_id;
}


int generareCod() {

    int n = citesteUltimulNumar("Clienti.txt");
    n++;
    return n;
}
class ExceptieGenerala : public exception {
protected:
    string mesaj;
public:
    explicit ExceptieGenerala(string mesaj) : mesaj(move(mesaj)) {}
    [[nodiscard]] const char* what() const noexcept override { return mesaj.c_str(); }
};

class ExceptieFisier : public ExceptieGenerala {
public:
    explicit ExceptieFisier(const string& fisier)
        : ExceptieGenerala("Eroare: Nu s-a putut deschide fisierul " + fisier) {}
};

class ExceptieOptiuneInvalida : public ExceptieGenerala {
public:
    ExceptieOptiuneInvalida() : ExceptieGenerala("Optiune invalida selectata!") {}
};

enum OptiuneServire {
    LaPachet,
    InRestaurant
};

class Client {
protected:
    string Nume;
    string Telefon;
    string Adresa;
    OptiuneServire Optiune;
    int Id_Client;
    int varsta{};
    int gen{};
    int inaltime{};
    int greutate{};
    int NrComenzi = 0;
    static int numarClienti;
    int pret{};

public:
    Client(int id, string nume, string telefon, string adresa, int nrComenzi = 0, OptiuneServire optiune = OptiuneServire::InRestaurant)
          : Nume(std::move(nume)), Telefon(std::move(telefon)), Adresa(std::move(adresa)), Optiune(optiune),
            Id_Client(id), varsta(0), gen(0), inaltime(0), greutate(0), NrComenzi(nrComenzi), pret(0) {}


    virtual ~Client() = default;

    Client(const Client& other)
        : Nume(other.Nume), Telefon(other.Telefon), Adresa(other.Adresa),
          Optiune(other.Optiune), Id_Client(other.Id_Client), varsta(other.varsta), gen(other.gen), inaltime(other.inaltime), greutate(other.greutate),
            NrComenzi(other.NrComenzi),pret(other.pret) {}



    Client& operator=(Client other) {
        swap(Id_Client, other.Id_Client);
        swap(Nume, other.Nume);
        swap(Telefon, other.Telefon);
        swap(Adresa, other.Adresa);
        swap(pret, other.pret);
        return *this;
    }


    [[nodiscard]] int getPret() const { return pret; }
    void setPret(int pretNou) { pret = pretNou; }

    [[nodiscard]] int getVarsta() const { return varsta; }
    [[nodiscard]] const string& getNume() const { return Nume; }
    [[nodiscard]] const string& getTelefon() const { return Telefon; }
    [[nodiscard]] const string& getAdresa() const { return Adresa; }
    [[nodiscard]] int getGen() const { return gen; }
    [[nodiscard]] int getInaltime() const { return inaltime; }
    [[nodiscard]] int getGreutate() const { return greutate; }
    [[nodiscard]] int getId_Client() const { return Id_Client; }
    [[nodiscard]] int getNrComenzi() const { return NrComenzi; }
    [[nodiscard]] OptiuneServire getOptiuneServire() const { return Optiune; }

    void setNume(const string& nume) { this->Nume = nume; }
    void setTelefon(const string& telefon) { this->Telefon = telefon; }
    void setAdresa(const string& adresa) { this->Adresa = adresa; }

    void setOptiuneServire(OptiuneServire optiune) {
        Optiune = optiune;
    }

    static void actualizeazaNRComanda(int id) {
        ifstream fisier("Clienti.txt");
        if (!fisier.is_open()) {
            throw FisierException("Nu s-a putut deschide fișierul Clienti.txt.");
        }

        string linie;
        string continutFisier;
        bool clientGasit = false;

        while (getline(fisier, linie)) {
            if (linie.find("ID: ") == 0) {
                int idFisier = stoi(linie.substr(4));
                if (idFisier == id) {
                    continutFisier += linie + "\n"; // ID

                    while (getline(fisier, linie) && linie.find("NrComenzi: ") != 0) {
                        continutFisier += linie + "\n";
                    }

                    int nrComenzi = stoi(linie.substr(11)) + 1;
                    continutFisier += "NrComenzi: " + to_string(nrComenzi) + "\n";

                    while (getline(fisier, linie)) {
                        continutFisier += linie + "\n";
                    }
                    break;
                }
            }

            if (!clientGasit) {
                continutFisier += linie + "\n";
            }
        }

        fisier.close();

        ofstream fisierOutput("Clienti.txt");
        if (!fisierOutput.is_open()) {
            throw FisierException("Nu s-a putut deschide fisierul pentru scriere.");
        }

        fisierOutput << continutFisier;
        fisierOutput.close();

        cout << "Numarul de comenzi a fost actualizat!" << endl;
    }
};


int Client::numarClienti = 0;



class Cont {
protected:
    unique_ptr<Client> client;
    int PretCont;

public:
    Cont(int id_client, const std::string& nume, const std::string& telefon, const std::string& adresa,
         int nrComenzi = 0, OptiuneServire optiune = OptiuneServire::InRestaurant,int pret=0)
        : client(std::make_unique<Client>(id_client, nume, telefon, adresa, nrComenzi, optiune)),PretCont(pret) {}

    Cont(Cont&& other) noexcept
        : client(std::move(other.client)), PretCont(other.PretCont) {}

    virtual ~Cont() = default;


    virtual double costlivrare() = 0;

    void salveazaInFisier() const {
        std::ofstream outFile("clienti.txt", std::ios::app);
        if (outFile.is_open()) {
            outFile << "ID Client: " << client->getId_Client() << "\n";
            outFile << "Nume: " << client->getNume() << "\n";
            outFile << "Telefon: " << client->getTelefon() << "\n";
            outFile << "Adresa: " << client->getAdresa() << "\n";
            outFile << "Optiune Servire: "
                    << (client->getOptiuneServire() == OptiuneServire::LaPachet ? "La Pachet" : "Restaurant") << "\n";
            outFile << "Numar Comenzi: " << client->getNrComenzi() << "\n";
            outFile << "Pret: " << client->getPret() << "\n";
            outFile << "-----------------------\n";
        } else {
            cout << "Eroare la deschiderea fișierului pentru salvare!" << std::endl;
        }
    }



    static int citesteUltimulNumar(const std::string& filename, int prefix) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            cout << "Eroare la deschiderea fișierului!" << std::endl;
            return -1;
        }

        std::string linie;
        int ultimul_id = -1;

        while (std::getline(file, linie)) {
            if (linie.find("ID:") == 0) {
                try {
                    int id = std::stoi(linie.substr(4));
                    if (id / 100 == prefix) {
                        ultimul_id = std::max(ultimul_id, id);
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Eroare la citirea ID-ului: " << e.what() << std::endl;
                }
            }
        }
        file.close();
        return ultimul_id;
    }

    static int generareCod(int prefix) {
        int n = citesteUltimulNumar("Clienti.txt", prefix);
        if (n == -1) {
            return prefix * 100 + 1;
        }
        return ++n;
    }

    [[nodiscard]] virtual std::unique_ptr<Cont> clone() const = 0;
};


class ContNormal : public Cont {
public:
    ContNormal(int id_client, const std::string& nume, const std::string& telefon, const std::string& adresa)
        : Cont(id_client, nume, telefon, adresa) {}


    double costlivrare() override {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 50);
        int costLivrare = dist(gen);
        return costLivrare;
    }

    [[nodiscard]] unique_ptr<Cont> clone() const override {
        return make_unique<ContNormal>(client->getId_Client(), client->getNume(),
                                            client->getTelefon(), client->getAdresa());
    }
};

class ContStandard : public Cont {
    static constexpr double costCont=15.5 ;
public:
    ContStandard(int id_client, const std::string& nume, const std::string& telefon, const std::string& adresa)
        : Cont(id_client, nume, telefon, adresa) {}

    static double getCostCont() {
        return costCont;
    }

    double costlivrare() override {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 50);
        double cost = dist(gen);
        /// ai reducere 10% la pretul de livrare daca  ai cont standard
        cost*=0.9;
        return cost;
    }

    [[nodiscard]] unique_ptr<Cont> clone() const override {
        return make_unique<ContNormal>(client->getId_Client(), client->getNume(),
                                            client->getTelefon(), client->getAdresa());
    }
};

class MeniuItem {
public:
    string nume;
    int calorii;
    float pret;
    string categorie;


    MeniuItem(string n, int c, float p, string cat)
        : nume(std::move(std::move(n))), calorii(c), pret(p), categorie(std::move(std::move(cat))) {}


    MeniuItem(const MeniuItem& other) = default;


};


class PlanAlimentar {
    int idClient;
    int calorii;

public:
    PlanAlimentar(int idClient, int caloriiDisponibile)
        : idClient(idClient), calorii(caloriiDisponibile) {}

   static string  trim(const string& str) {
        size_t first = str.find_first_not_of(' ');
        size_t last = str.find_last_not_of(' ');
        return (first == string::npos || last == string::npos) ? "" : str.substr(first, (last - first + 1));
    }


    static vector<MeniuItem> citesteProduseDinFisier(const string& fisier, const string& categorie) {
        ifstream f(fisier);
        vector<MeniuItem> produse;
        string linie;

        if (!f.is_open()) {
            cerr << "eroare la deschiderea fisierului " << fisier << endl;
            return produse;
        }

        while (getline(f, linie)) {
            stringstream ss(linie);
            string nume;
            int calorii;
            float pret;


            getline(ss, nume, ',');
            ss >> pret;
            ss.ignore(1, ',');
            ss >> calorii;


            produse.emplace_back(trim(nume), calorii, pret, categorie);
        }

        return produse;
    }




    static void amestecaProduse(vector<MeniuItem>& produse) {

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<std::vector<MeniuItem>::size_type> distrib(0, produse.size() - 1);


        for (vector<MeniuItem>::size_type i = produse.size() - 1; i > 0; --i) {
            vector<MeniuItem>::size_type j = distrib(gen);  // Alege un index aleatoriu între 0 și i
            std::swap(produse[i], produse[j]);  // Schimbă elementele
        }
    }




    void construiesteMeniu(int nrZile, bool alegereManuala = false) const {
    vector<MeniuItem> produseMicDejun = citesteProduseDinFisier("micdejun.txt", "MicDejun");
    vector<MeniuItem> produsePranz = citesteProduseDinFisier("pranz.txt", "Pranz");
    vector<MeniuItem> produseCina = citesteProduseDinFisier("cina.txt", "Cina");
    vector<MeniuItem> produseDesert = citesteProduseDinFisier("gustari.txt", "Desert");

    int caloriiZi = calorii;
    float totalPret = 0.0;

    for (int zi = 1; zi <= nrZile; ++zi) {
        cout << "\n--- ziua " << zi << " ---\n";
        cout << "calorii disponibile pentru ziua " << zi << ": " << caloriiZi << "\n";

        int caloriiDisponibile = caloriiZi;
        vector<MeniuItem> meniuZi;

        if (alegereManuala) {
            cout << "Alege produsele pentru ziua " << zi << ":\n";

            // Alege mic dejun
            cout << "\nAlege un mic dejun:\n";
            for (int i = 0; i < produseMicDejun.size(); ++i) {
                cout << i + 1 << ". " << produseMicDejun[i].nume << " | calorii: " << produseMicDejun[i].calorii << " | pret: " << produseMicDejun[i].pret << " lei\n";
            }
            int alegere;
            cin >> alegere;
            alegere--;
            if (produseMicDejun[alegere].calorii <= caloriiDisponibile) {
                meniuZi.push_back(produseMicDejun[alegere]);
                caloriiDisponibile -= produseMicDejun[alegere].calorii;
                totalPret += produseMicDejun[alegere].pret;
            } else {
                cout << "Alegerea depaseste numarul de calorii disponibile.\n";
                continue;
            }


            cout << "\nAlege un pranz:\n";
            for (int i = 0; i < produsePranz.size(); ++i) {
                cout << i + 1 << ". " << produsePranz[i].nume << " | calorii: " << produsePranz[i].calorii << " | pret: " << produsePranz[i].pret << " lei\n";
            }
            cin >> alegere;
            alegere--;
            if (produsePranz[alegere].calorii <= caloriiDisponibile) {
                meniuZi.push_back(produsePranz[alegere]);
                caloriiDisponibile -= produsePranz[alegere].calorii;
                totalPret += produsePranz[alegere].pret;
            } else {
                cout << "Alegerea depaseste numarul de calorii disponibile.\n";
                continue;
            }


            cout << "\nAlege o cina:\n";
            for (int i = 0; i < produseCina.size(); ++i) {
                cout << i + 1 << ". " << produseCina[i].nume << " | calorii: " << produseCina[i].calorii << " | pret: " << produseCina[i].pret << " lei\n";
            }
            cin >> alegere;
            alegere--;
            if (produseCina[alegere].calorii <= caloriiDisponibile) {
                meniuZi.push_back(produseCina[alegere]);
                caloriiDisponibile -= produseCina[alegere].calorii;
                totalPret += produseCina[alegere].pret;
            } else {
                cout << "Alegerea depaseste numarul de calorii disponibile.\n";
                continue;
            }


            cout << "\nAlege un desert:\n";
            for (int i = 0; i < produseDesert.size(); ++i) {
                cout << i + 1 << ". " << produseDesert[i].nume << " | calorii: " << produseDesert[i].calorii << " | pret: " << produseDesert[i].pret << " lei\n";
            }
            cin >> alegere;
            alegere--;
            if (produseDesert[alegere].calorii <= caloriiDisponibile) {
                meniuZi.push_back(produseDesert[alegere]);
                caloriiDisponibile -= produseDesert[alegere].calorii;
                totalPret += produseDesert[alegere].pret;
            } else {
                cout << "Alegerea depaseste numarul de calorii disponibile.\n";
                continue;
            }
        } else {

            vector<MeniuItem> produseDeZi;
            produseDeZi.insert(produseDeZi.end(), produseMicDejun.begin(), produseMicDejun.end());
            produseDeZi.insert(produseDeZi.end(), produsePranz.begin(), produsePranz.end());
            produseDeZi.insert(produseDeZi.end(), produseCina.begin(), produseCina.end());
            produseDeZi.insert(produseDeZi.end(), produseDesert.begin(), produseDesert.end());

            amestecaProduse(produseDeZi);


            while (caloriiDisponibile > 0 && !produseDeZi.empty()) {
                bool produsAdaugat = false;

                for (auto it = produseDeZi.begin(); it != produseDeZi.end(); ++it) {
                    if (it->calorii <= caloriiDisponibile) {
                        meniuZi.push_back(*it);
                        caloriiDisponibile -= it->calorii;
                        totalPret += it->pret;

                        it = produseDeZi.erase(it);
                        produsAdaugat = true;
                        break;
                    }
                }


                if (!produsAdaugat) {
                    break;
                }
            }
        }


        cout << "Meniul pentru ziua " << zi << ":\n";
        for (auto& produs : meniuZi) {
            cout << produs.nume << " | calorii: " << produs.calorii << " | pret: " << produs.pret << " lei\n";
        }


        if (caloriiDisponibile > 0) {
            cout << "Mai raman " << caloriiDisponibile << " calorii.\n";
        }
    }


    cout << "\nTotal pret pentru " << nrZile << " zile: " << fixed << setprecision(2) << totalPret << " lei\n";
}


};


string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, (last - first + 1));
}

int getCaloriiById(int id) {
    ifstream fisier("Clienti.txt");
    if (!fisier.is_open()) {
        cerr << "Eroare la deschiderea fisierului Clienti.txt!" << endl;
        return -1;
    }

    string linie;
    while (getline(fisier, linie)) {

        if (linie.find("ID: ") == 0) {
            int idFisier = stoi(linie.substr(4));
            if (idFisier == id) {

                while (getline(fisier, linie)) {
                    if (linie.find("Calorii: ") == 0) {
                        string caloriiStr = linie.substr(9);
                        caloriiStr = trim(caloriiStr);


                        try {
                            return stoi(caloriiStr);
                        }
                        catch (const invalid_argument& e) {
                            cout << "Eroare la citirea caloriilor pentru clientul cu ID-ul " << id << endl;
                            return -1;
                        }
                    }
                }
            }
        }
    }

    return -1;
}

class ContPremium : public Cont {
    static constexpr double costCont = 20.0;
    Obiectiv* obiectiv{};
    unique_ptr<Client> client{};
    int greutate{};
    int inaltime{};
    int varsta{};
    int gen{};


public:
    explicit ContPremium(std::unique_ptr<Client> clientPtr)
    : Cont(clientPtr->getId_Client(), clientPtr->getNume(), clientPtr->getTelefon(), clientPtr->getAdresa()),
      client(move(clientPtr)){}

    explicit ContPremium(int id, const std::string& nume, const std::string& telefon, const std::string& adresa)
    : Cont(id, nume, telefon, adresa),
      client(std::make_unique<Client>(id, nume, telefon, adresa)) {}


    ~ContPremium() override {
        delete obiectiv;
    }

    static double getCostCont() {
        return costCont;
    }

    double costlivrare() override {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(1, 50);
        double costLivrare = dist(gen);
        // reducere de 15% pentru livrare la cont premium
        costLivrare *= 0.85;
        return costLivrare;
    }

    void setObiectiv(Obiectiv* obj) {
        delete obiectiv;
        obiectiv = obj;
    }

    static Obiectiv* alegeObiectiv() {
        int optiune;
        cout << "Alege obiectivul:\n";
        cout << "1. Slabire\n";
        cout << "2. Crestere masa musculara\n";
        cout << "3. Mentinere\n";
        cout << "Alegere: ";
        cin >> optiune;

        unique_ptr<Obiectiv> obj;
        switch (optiune) {
            case 1:
                obj = std::make_unique<Slabire>();
            break;
            case 2:
                obj = std::make_unique<MasaMusculara>();
            break;
            case 3:
                throw std::logic_error("Mentinere nu este implementat.");
            default:
                throw ExceptieOptiuneInvalida();
        }

        return obj.release();
    }


    [[nodiscard]] int calculeazaNecesarCaloric() const {
        if (obiectiv) {
            return obiectiv->calculeazaCalorii(greutate, inaltime, varsta, gen);
        }
        throw runtime_error("Obiectivul nu este setat.");
    }

    [[nodiscard]] std::unique_ptr<Cont> clone() const override {
        auto cont = std::make_unique<ContPremium>(std::make_unique<Client>(*client));
        if (obiectiv) {
            cont->setObiectiv(obiectiv);
        }
        return cont;
    }

    void setDetaliiUtilizator(int greutate_, int inaltime_, int varsta_, int gen_) {
        greutate = greutate_;
        inaltime = inaltime_;
        varsta = varsta_;
        gen = gen_;
    }

    void genereazaPlanAlimentar() const {
        int calorii = getCaloriiById(client->getId_Client());
        PlanAlimentar plan(client->getId_Client(), calorii);

        int nrZile = 7;
        plan.construiesteMeniu(nrZile, false);
        cout << "Comanda va ajunge in jurul orei 18:00 la adresa din cont.\n";
    }

    static void rezervaMasa() {
        try {
            ifstream fisier("mese.txt");
            if (!fisier.is_open()) {
                throw FisierException("Nu s-a putut deschide fișierul mese.txt.");
            }

            vector<pair<int, bool>> mese(5, { 0, false });
            string linie;


            int masaIndex = 0;
            vector<string> ore = {
                "18:00 - 20:00",
                "20:00 - 22:00",
                "22:00 - 00:00"
            };


            while (getline(fisier, linie)) {
                if (linie.find("rezervata") != string::npos) {
                    mese[masaIndex].second = true; // masa rezervata
                }
                masaIndex++;
            }


            int alegere;
            bool intervalDisponibil = false;
            while (!intervalDisponibil) {
                cout << "Alege un interval orar pentru rezervare:\n";
                for (int i = 0; i < ore.size(); ++i) {
                    cout << i + 1 << ". " << ore[i] << endl;
                }

                cin >> alegere;


                if (alegere < 1 || alegere > 3) {
                    cout << "Optiune invalida. Te rog alege un interval valid.\n";
                    continue;
                }


                int masaAleasa = -1;
                for (int i = 0; i < mese.size(); ++i) {
                    if (!mese[i].second) {
                        masaAleasa = i;
                        break;
                    }
                }

                if (masaAleasa == -1) {
                    cout << "Nu mai sunt mese disponibile pentru acest interval.\n";
                    cout << "Te rugam sa alegi un alt interval.\n";
                }
                else {
                    intervalDisponibil = true;

                    cout << "Ai ales masa " << masaAleasa + 1 << " pentru intervalul " << ore[alegere - 1] << ".\n";
                    mese[masaAleasa].second = true;


                    ofstream outFisier("mese.txt");
                    if (!outFisier.is_open()) {
                        throw FisierException("Nu s-a putut deschide fișierul mese.txt pentru scriere.");
                    }

                    for (int i = 0; i < mese.size(); ++i) {
                        outFisier << "Masa " << i + 1 << " " << ore[i] << " este " << (mese[i].second ? "rezervata" : "disponibila") << "\n";
                    }


                    cout << "\n--- Confirmare rezervare ---\n";
                    cout << "Ati rezervat Masa " << masaAleasa + 1 << " pentru intervalul " << ore[alegere - 1] << ".\n";
                    cout << "Masa va fi pregatita pana la sosirea dumneavoastra.\n";
                    cout << "Va asteptam cu drag!\n";
                }
            }
    }
    catch (const FisierException& e) {
        cout << "Eroare la rezervarea mesei: " << e.what() << endl;
    }
}
};


enum Sport {
    Sala ,
    Inot,
    Yoga,
    Box
};


struct Antrenor {
    string nume;
    string specializare;
    double tarif;

    Antrenor(string  nume, string  specializare, double tarif)
        : nume(std::move(nume)), specializare(std::move(specializare)), tarif(tarif) {}
};


class ContVip:public Cont {
    unique_ptr<Client>client{};
    static constexpr double costCont = 20.5;
    Obiectiv* obiectiv{};
    int greutate{};
    int inaltime{};
    int varsta{};
    int gen{};
    Sport sportAles;
    Antrenor antrenorAles;
    string oraAleasaFinala;
    string ziAleasaFinala;

    public:
    ContVip(int id_client, const std::string& nume, const std::string& telefon, const std::string& adresa,
        int nrComenzi = 0, OptiuneServire optiune = OptiuneServire::InRestaurant, int pret = 0)
    : Cont(id_client, nume, telefon, adresa, nrComenzi, optiune, pret), sportAles(Sport::Sala),
      antrenorAles("Default Nume", "Default Specializare", 0.0) {}

    static double getCostCont() {
        return costCont;
    }

    void setDetaliiUtilizator(int greutate_, int inaltime_, int varsta_, int gen_) {
        greutate = greutate_;
        inaltime = inaltime_;
        varsta = varsta_;
        gen = gen_;
    }

    double costlivrare() override {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(1, 50);
        double costLivrare = dist(gen);
        // reducere de 25% pentru livrare la cont premium
        costLivrare *= 0.75;
        return costLivrare;
    }

    void setObiectiv(Obiectiv* obj) {
        delete obiectiv;
        obiectiv = obj;
    }



    static Obiectiv* alegeObiectiv() {
        int optiune;
        cout << "Alege obiectivul:\n";
        cout << "1. Slabire\n";
        cout << "2. Crestere masa musculara\n";
        cout << "3. Mentinere\n";
        cout << "Alegere: ";
        cin >> optiune;


        switch (optiune) {
            case 1: return new Slabire();
            case 2: return new MasaMusculara();
            case 3: return new Mentinere();
            default:
                throw ExceptieOptiuneInvalida();
        }
    }


    [[nodiscard]] int calculeazaNecesarCaloric() const {
        if (obiectiv) {
            return obiectiv->calculeazaCalorii(greutate, inaltime, varsta, gen);
        }
        throw runtime_error("Obiectivul nu este setat.");
    }

    void genereazaPlanAlimentar() const {
        int calorii = getCaloriiById(client->getId_Client());
        PlanAlimentar plan(client->getId_Client(), calorii);

        int nrZile = 7;
        plan.construiesteMeniu(nrZile, false);
        cout << "Comanda va ajunge in jurul orei 18:00 la adresa din cont.\n";
    }


    static void rezervaMasa() {
        try {
            ifstream fisier("mese.txt");
            if (!fisier.is_open()) {
                throw FisierException("Nu s-a putut deschide fișierul mese.txt.");
            }

            vector<pair<int, bool>> mese(5, { 0, false });
            string linie;


            int masaIndex = 0;
            vector<string> ore = {
                "18:00 - 20:00",
                "20:00 - 22:00",
                "22:00 - 00:00"
            };


            while (getline(fisier, linie)) {
                if (linie.find("rezervata") != string::npos) {
                    mese[masaIndex].second = true; // masa rezervata
                }
                masaIndex++;
            }


            int alegere;
            bool intervalDisponibil = false;
            while (!intervalDisponibil) {
                cout << "Alege un interval orar pentru rezervare:\n";
                for (int i = 0; i < ore.size(); ++i) {
                    cout << i + 1 << ". " << ore[i] << endl;
                }

                cin >> alegere;


                if (alegere < 1 || alegere > 3) {
                    cout << "Optiune invalida. Te rog alege un interval valid.\n";
                    continue;
                }


                int masaAleasa = -1;
                for (int i = 0; i < mese.size(); ++i) {
                    if (!mese[i].second) {
                        masaAleasa = i;
                        break;
                    }
                }

                if (masaAleasa == -1) {
                    cout << "Nu mai sunt mese disponibile pentru acest interval.\n";
                    cout << "Te rugam sa alegi un alt interval.\n";
                }
                else {
                    intervalDisponibil = true;

                    cout << "Ai ales masa " << masaAleasa + 1 << " pentru intervalul " << ore[alegere - 1] << ".\n";
                    mese[masaAleasa].second = true;


                    ofstream outFisier("mese.txt");
                    if (!outFisier.is_open()) {
                        throw FisierException("Nu s-a putut deschide fișierul mese.txt pentru scriere.");
                    }

                    for (int i = 0; i < mese.size(); ++i) {
                        outFisier << "Masa " << i + 1 << " " << ore[i] << " este " << (mese[i].second ? "rezervata" : "disponibila") << "\n";
                    }


                    cout << "\n--- Confirmare rezervare ---\n";
                    cout << "Ati rezervat Masa " << masaAleasa + 1 << " pentru intervalul " << ore[alegere - 1] << ".\n";
                    cout << "Masa va fi pregatita pana la sosirea dumneavoastra.\n";
                    cout << "Va asteptam cu drag!\n";
                }
            }
    }
    catch (const FisierException& e) {
        cout << "Eroare la rezervarea mesei: " << e.what() << endl;
    }
}

    void alegeSport() {
        cout << "Alege tipul de sport:\n";
        cout << "1. Sala\n";
        cout << "2. Inot\n";
        cout << "3. Yoga\n";
        cout << "4. Box\n";

        int alegere;
        cin >> alegere;

        // Verificăm dacă alegerea este validă
        if (alegere < 1 || alegere > 4) {
            cout << "Optiune invalida.\n";
            return;
        }

        sportAles = static_cast<Sport>(alegere - 1); // Corectăm offset-ul
        cout << "Ai ales sportul: " << getSportString() << endl;

        alegeZiSiOra();
        verificaLocuriDisponibile();
    }

    [[nodiscard]] string getSportString() const {

        if (sportAles < 0 || sportAles >= Sport::Box) {
            return "Sport necunoscut";
        }

        switch (sportAles) {
            case Sala: return "Sala";
            case Inot: return "Inot";
            case Yoga: return "Yoga";
            case Box: return "Box";
            default: return "Sport necunoscut";
        }
    }


    void alegeAntrenor() {
        vector<Antrenor> antrenoriDisponibili;

        if (sportAles == Sala) {
            antrenoriDisponibili = {
                Antrenor("Ion Popescu", "Fitness", 50.0),
                Antrenor("Maria Ionescu", "Cardio", 60.0)
            };
        } else if (sportAles == Inot) {
            antrenoriDisponibili = {
                Antrenor("Vasile Georgescu", "Inot liber", 40.0),
                Antrenor("Ana Mihail", "Inot competitional", 55.0)
            };
        } else if (sportAles == Yoga) {
            antrenoriDisponibili = {
                Antrenor("Elena Popa", "Yoga", 70.0),
                Antrenor("Ioana Radu", "Yoga relaxare", 65.0)
            };
        } else if (sportAles == Box) {
            antrenoriDisponibili = {
                Antrenor("Florin Iulian", "Box", 75.0),
                Antrenor("Mihail Tudor", "Box profesionist", 85.0)
            };
        }

        cout << "Alege un antrenor:\n";
        for (size_t i = 0; i < antrenoriDisponibili.size(); ++i) {
            cout << i + 1 << ". " << antrenoriDisponibili[i].nume << " - " << antrenoriDisponibili[i].specializare
                 << " - " << antrenoriDisponibili[i].tarif << " lei/sesiune\n";
        }

        int alegereAntrenor;
        cin >> alegereAntrenor;

        if (alegereAntrenor < 1 || alegereAntrenor > static_cast<int>(antrenoriDisponibili.size())) {
            cout << "Optiune invalida.\n";
            return;
        }

        antrenorAles = antrenoriDisponibili[alegereAntrenor - 1];
        cout << "Ai ales antrenorul: " << antrenorAles.nume << ", specializare: " << antrenorAles.specializare << ".\n";
    }



    void alegeZiSiOra() {
        vector<string> zileDisponibile = {"Luni", "Marti", "Miercuri", "Joi", "Vineri"};
        vector<string> oreDisponibile;

        if (sportAles == Sala) {
            oreDisponibile = {"08:00", "10:00", "12:00", "14:00", "16:00", "18:00"};
        } else if (sportAles == Inot) {
            oreDisponibile = {"09:00", "11:00", "13:00", "15:00", "17:00"};
        } else if (sportAles == Yoga) {
            oreDisponibile = {"07:00", "09:00", "11:00", "13:00", "15:00"};
        } else if (sportAles == Box) {
            oreDisponibile = {"08:00", "10:00", "12:00", "14:00", "16:00"};
        }

        cout << "Alege ziua pentru antrenament:\n";
        for (int i = 0; i < zileDisponibile.size(); ++i) {
            cout << i + 1 << ". " << zileDisponibile[i] << endl;
        }

        int ziAlesa;
        cin >> ziAlesa;

        if (ziAlesa < 1 || ziAlesa > zileDisponibile.size()) {
            cout << "Ziua aleasă este invalidă.\n";
            return;
        }

        cout << "Ai ales ziua: " << zileDisponibile[ziAlesa - 1] << endl;

        cout << "Alege ora pentru antrenament:\n";
        for (int i = 0; i < oreDisponibile.size(); ++i) {
            cout << i + 1 << ". " << oreDisponibile[i] << endl;
        }

        int oraAleasa;
        cin >> oraAleasa;

        if (oraAleasa < 1 || oraAleasa > oreDisponibile.size()) {
            cout << "Ora aleasă este invalidă.\n";
            return;
        }

        cout << "Ai ales ora: " << oreDisponibile[oraAleasa - 1] << " pentru antrenament.\n";

        oraAleasaFinala = oreDisponibile[oraAleasa - 1];
        ziAleasaFinala = zileDisponibile[ziAlesa - 1];
    }


    void verificaLocuriDisponibile() const {
        vector<int> locuriDisponibile = {5, 1, 3, 2, 1, 2};

        int indexOra = -1;
        vector<string> oreDisponibile = {"08:00", "10:00", "12:00", "14:00", "16:00", "18:00"};

        for (int i = 0; i < oreDisponibile.size(); ++i) {
            if (oraAleasaFinala == oreDisponibile[i]) {
                indexOra = i;
                break;
            }
        }

        if (indexOra != -1 && locuriDisponibile[indexOra] > 0) {
            locuriDisponibile[indexOra]--;
            cout << "Locuri disponibile pentru ora aleasă.\n";
        } else {
            cout << "Nu mai sunt locuri disponibile pentru ora aleasa.\n";
        }
    }

    [[nodiscard]] unique_ptr<Cont> clone() const override {
        return make_unique<ContNormal>(client->getId_Client(), client->getNume(),
                                            client->getTelefon(), client->getAdresa());
    }



};



enum OptiuneCont { Normal, Standard, Premium,VIP };

class ClientNou : public Client {

    unique_ptr<Obiectiv>obiectiv;
    OptiuneCont tipCont;
    int calorizilnice=0;
    Sport sportAles;
    string dataExpirareAbonament;
    int caloriiZilnice{};
    public:

    ClientNou(int id, const std::string& nume, const std::string& telefon, const std::string& adresa)
    : Client(id, nume, telefon, adresa), tipCont(Normal), sportAles(Sport::Sala) {}

    ClientNou()
        : Client(-1, "Necunoscut", "Necunoscut", "Necunoscut"), tipCont(Normal), sportAles(Sport::Sala) {}

    [[nodiscard]] const unique_ptr<Obiectiv>& getObiectiv() const {
        return obiectiv;
    }


    void setDataExpirare(int luni) {
        time_t now = time(nullptr);
        tm* localtm = localtime(&now);
        // adaugam luni la data curenta
        localtm->tm_mon += luni;  // adauga luni la data curenta

        // calculam data de expirare
        mktime(localtm);  // normalizeaza structura tm
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%d-%m-%Y", localtm);
        dataExpirareAbonament = string(buffer);
    }


    void citesteDate() {
        cout << "Introduceti numele: ";
        cin.ignore();
        getline(cin, Nume);
        cout << "Introduceti telefonul: ";
        getline(cin, Telefon);
        cout << "Introduceti adresa: ";
        getline(cin, Adresa);
        cout << "Introduceti varsta: ";
        cin >> varsta;
        cout << "Introduceti greutatea (kg): ";
        cin >> greutate;
        cout << "Introduceti inaltimea (cm): ";
        cin >> inaltime;
        cout << "Introduceti genul (1 - Masculin, 2 - Feminin): ";
        cin >> gen;

        int optiuneCont;
        cout << "Alegeti tipul de cont:\n";
        cout << "1 - Cont normal: 0 RON\n";
        cout << "2 - Cont Standard: 15% reducere la transport  - 10 RON\n";
        cout << "3 - Cont Premium: Plan alimentar + rezervare masa + 20% reducere la transport - 25 RON\n";
        cout << "4 - Cont Vip:  Plan alimentar + antrenamente + transport gratis + 40% reducere la transport - 35 RON\n";
        cout << "Pretul pentru crearea contului va fi activat la momentul realizarii unei comenzi.\n";
        cout << "Alegere: ";

        if (!(cin >> optiuneCont)) {
            throw ExceptieOptiuneInvalida();
        }

        if (optiuneCont == 1) {
            tipCont = OptiuneCont::Normal;
            ContNormal contNormal(0, Nume, Telefon, Adresa);
            Id_Client = ContNormal::generareCod(11);
            setDataExpirare(1);  // 1 luna pentru Normal

        }

        else if (optiuneCont == 2) {
            tipCont = OptiuneCont::Standard;
            ContNormal contStandard(0, Nume, Telefon, Adresa);
            Id_Client = ContNormal::generareCod(22);
            setDataExpirare(1);
        }

        else if (optiuneCont == 3) {
            tipCont = OptiuneCont::Premium;
            ContPremium contPremium(0, Nume, Telefon, Adresa);

            try {
                Obiectiv* obj = ContPremium::alegeObiectiv();
                contPremium.setObiectiv(obj);

                if (obj != nullptr) {
                    cout << "Obiectiv ales: " << obj->getObiectivString() << "\n";

                    caloriiZilnice = obj->calculeazaCalorii(greutate, inaltime, varsta, gen);
                    cout << "Necesar caloric pentru obiectivul ales: " << caloriiZilnice << " calorii.\n";
                } else {
                    cout << "Obiectivul nu a fost ales corect. Setarea calorii la 0.\n";
                    caloriiZilnice = 0;
                }
            }
            catch (const exception& e) {
                cout << "Eroare: " << e.what() << endl;
                caloriiZilnice = 0;
            }

            setDataExpirare(1);
            Id_Client = ContPremium::generareCod(33);
        }

        if (optiuneCont == 4) {
            tipCont = OptiuneCont::VIP;
            Antrenor antrenor("Ion Popescu", "Fitness", 50.0);
            ContVip contVIP(0, Nume, Telefon, Adresa, 0);

            contVIP.alegeSport();
            contVIP.alegeAntrenor();
            Id_Client = ContVip::generareCod(44);
            try {
                Obiectiv* obj = ContPremium::alegeObiectiv();
                contVIP.setObiectiv(obj);

                if (obj != nullptr) {
                    cout << "Obiectiv ales: " << obj->getObiectivString() << "\n";

                    caloriiZilnice = obj->calculeazaCalorii(greutate, inaltime, varsta, gen);
                    cout << "Necesar caloric pentru obiectivul ales: " << caloriiZilnice << " calorii.\n";
                } else {
                    cout << "Obiectivul nu a fost ales corect. Setarea calorii la 0.\n";
                    caloriiZilnice = 0;
                }
            }catch (const exception& e) {
                cout << "Eroare: " << e.what() << endl;
                caloriiZilnice = 0;  // Dacă apare o eroare, setează caloriiZilnice la 0
            }
            setDataExpirare(1);
            setDataExpirare(1);
        }

    }

    void salveazaInFisier(const string& fisier) const {
        ofstream out(fisier, ios::app);
        if (!out) {
            throw ExceptieFisier(fisier);
        }

        out << "ID: " << Id_Client << "\n"
            << "Nume: " << Nume << "\n"
            << "Telefon: " << Telefon << "\n"
            << "Adresa: " << Adresa << "\n"
            << "Varsta: " << varsta << "\n"
            << "Greutate: " << greutate << " kg\n"
            << "Inaltime: " << inaltime << " cm\n"
            <<"NrComenzi: "<<"0\n"
            << "Gen: " << (gen == 1 ? "Masculin" : "Feminin") << "\n";

        if (caloriiZilnice > 0) {
            out << "Calorii: " << caloriiZilnice << "\n";
        }
        else {
            out << "Calorii: -\n";
        }



        out << "Data expirare abonament: " << dataExpirareAbonament << "\n";
        out << "---------------------------\n";

        cout << "\nClientul a fost inregistrat cu succes! ID-ul clientului este: " << Id_Client << "\n";
    }

};


class InterfataUtilizator {
    unique_ptr<Client> client;
    bool trecePeste = false;
    int calorii{};
    public:
    InterfataUtilizator() : client(nullptr){}


    void pornire() {
    cout << "      Bine ati venit la HELLO FRESH!\n";
    cout << "     -------------------------------\n";

    while (true) {
        if (!trecePeste) {
            cout << "Introduceti ID-ul: ";
            int id;
            cin >> id;

            try {
                if (verificaId(id, client)) {
                    cout << "ID valid! Puteti comanda mancare.\n";
                    if (id / 100 == 33 || id / 100 == 22) {
                        int optiuneBox, generare;
                        cout << "Doriti sa comandati un plan alimentar (la pachet)? (1 - Da, 0 - Nu): ";
                        cin >> optiuneBox;
                        cout << "Doriti sa generam noi un meniu personalizat pentru dumneavoastra? (1-Da, 0-Nu): ";
                        cin >> generare;

                        if (optiuneBox == 1) {
                            int nrzile;
                            client->setOptiuneServire(LaPachet);
                            cout << "Pentru cate zile doriti planul alimentar: ";
                            cin >> nrzile;

                            if (generare == 1) {
                                calorii = getCaloriiById(client->getId_Client());
                                PlanAlimentar plan(client->getId_Client(), calorii);
                                plan.construiesteMeniu(nrzile, false); //
                                cout << "Comanda va ajunge in jurul orei 18:00 la adresa din cont.\n";
                            } else {
                                calorii = getCaloriiById(client->getId_Client());
                                PlanAlimentar plan(client->getId_Client(), calorii);
                                plan.construiesteMeniu(nrzile, true); // alegere manuala
                                cout << "---Comanda a fost plasata-----\n";
                                cout << "---Va ajunge in jurul orei 18:00 la adresa din cont";
                            }
                        }
                    }


                    if (id / 100 == 33 || id / 100 == 22) {
                        int optiuneServire;
                        cout << "Alege optiunea de servire:\n";
                        cout << "1. La restaurant (rezervare masa)\n";
                        cout << "2. La pachet\n";
                        cout << "Alegere: ";
                        cin >> optiuneServire;

                        try {
                            switch (optiuneServire) {
                            case 1: {
                                client->setOptiuneServire(InRestaurant);
                                if (id / 100 == 33) {
                                    ContVip::rezervaMasa();
                                }
                                break;
                            }
                            case 2:
                                client->setOptiuneServire(LaPachet);
                                break;
                            default:
                                throw ProdusInvalidException("Optiune invalida.");
                            }
                        } catch (const ProdusInvalidException& e) {
                            cout << e.what() << endl;
                            continue;
                        }
                    } else {
                        cout << "Nu aveti acces la rezervarea mesei.\n";
                    }

                    // continua comanda
                    MeniuPrincipal meniu;
                    afiseazaComanda(meniu, client);
                    break;
                } else {
                    afiseazaOptiuni(trecePeste);
                }
            } catch (const FisierException& e) {
                cout << "Eroare la citirea fisierului: " << e.what() << endl;
                break;
            }
        } else {
            // daca treci peste, creezi un client temporar
            client = make_unique<Client>(-1, "Client fara cont", "Necunoscut", "Necunoscut");
            MeniuPrincipal meniu;
            afiseazaComanda(meniu, client);
            break;
        }
    }
}

    static bool verificaId(int id, unique_ptr<Client>& client) {
        ifstream fisier("Clienti.txt");
        if (!fisier.is_open()) {
            throw FisierException("Nu s-a putut deschide fisierul Clienti.txt.");
        }

        string linie;
        while (getline(fisier, linie)) {
            if (linie.find("ID: ") == 0) {
                int idFisier = stoi(linie.substr(4));  // Problema aici poate fi din cauza substr(4)
                if (idFisier == id) {
                    string nume, telefon, adresa;
                    int nrComenzi = 0;  // Inițializăm nrComenzi
                    getline(fisier, linie);
                    if (linie.find("Nume: ") == 0) nume = linie.substr(6);
                    getline(fisier, linie);
                    if (linie.find("Telefon: ") == 0) telefon = linie.substr(9);
                    getline(fisier, linie);
                    if (linie.find("Adresa: ") == 0) adresa = linie.substr(8);
                    getline(fisier, linie);
                    if (linie.find("NrComenzi: ") == 0) nrComenzi = stoi(linie.substr(11));

                    client = make_unique<Client>(idFisier, nume, telefon, adresa, nrComenzi);
                    return true;
                }
            }
        }

        return false;
    }


    static void afiseazaOptiuneServire(const unique_ptr<Client>& client, InterfataUtilizator& interfata) {
    int optiuneServire = 0;

    while (true) {  // Buclă pentru a repeta în caz de opțiune invalidă
        try {
            cout << "Alege optiunea de servire:\n";
            cout << "1. La restaurant\n";
            cout << "2. La pachet\n";
            cout << "Alegere: ";
            cin >> optiuneServire;

            if (cin.fail()) {
                throw ProdusInvalidException("Introduceti o valoare valida.");
            }

            switch (optiuneServire) {
                case 1:
                    client->setOptiuneServire(InRestaurant);
                    if (client->getId_Client() / 100 == 44) { // verifica daca utilizatorul este VIP
                        ContVip::rezervaMasa(); // acceseaza contvip prin obiectul InterfataUtilizator
                    }
                    return;  // Ieșim din buclă (funcția s-a terminat cu succes)
                case 2:
                    client->setOptiuneServire(LaPachet);
                    return;  // Ieșim din buclă (funcția s-a terminat cu succes)
                default:
                    throw ProdusInvalidException("Optiune invalida.");
            }
        } catch (const ProdusInvalidException& e) {
            cout << e.what() << endl;
            // Continuăm să cerem opțiunea până când utilizatorul introduce o opțiune validă
        }
    }
}



static void afiseazaComanda(MeniuPrincipal& meniu, const unique_ptr<Client>& client) {
    int optiune;
    bool continuare = true;
    vector<pair<unique_ptr<Produs>, int>> comanda;

   double total = 0;
    int nrComenzi = client->getNrComenzi();


    while (continuare) {
        afiseazaTipMeniu();
        cin >> optiune;

        switch (optiune) {
        case 1:
            meniu.citesteProduseDinFisier("meniu.txt");
            break;
        case 2:
            meniu.citesteProduseDinFisier("meniuBar");
            break;
        case 3:
            meniu.citesteProduseDinFisier("meniuDesert.txt");
            break;
        default:
            cout << "Optiune invalida. Te rog alege din nou.\n";
            continue;
        }

        meniu.afiseazaMeniu();

        cout << "Alege un produs (indice): ";
        int produsSelectat;
        cin >> produsSelectat;

        if (produsSelectat > 0 && produsSelectat <= meniu.getNrProduse()) {
            const auto& produs = meniu.getProduse()[produsSelectat - 1];
            cout << "Ai ales: " << produs->getNume() << "\n";

            int cantitate;
            cout << "Cate portii doresti? ";
            cin >> cantitate;

            comanda.emplace_back(produs->clone(), cantitate);
            cout << "Ai adaugat " << cantitate << " portii de " << produs->getNume() << "\n";
        }
        else {
            cout << "Index invalid!\n";
        }

        cout << "Vrei sa adaugi alt produs? (1 pentru da, 0 pentru nu): ";
        cin >> continuare;
    }

    cout << "\n--- Comanda Finala ---\n";
    if (client) {
        cout << "Client: " << client->getNume() << "\n";
        cout << "ID_CLIENT: " << client->getId_Client() << "\n";
        cout << "Telefon: " << client->getTelefon() << "\n";
        cout << "Adresa: " << client->getAdresa() << "\n";
    }
    else {
        cout << "Client:------\n";
    }




    for (const auto& [produs, cantitate] : comanda) {
        cout << "Produs: " << produs->getNume()
            << ", Cantitate: " << cantitate
            << ", Pret unitar: " << produs->getPret() << " lei\n";
        total += produs->getPret() * cantitate;
    }

    if (client) {

        if (client->getNrComenzi() % 5 == 0 && client->getNrComenzi() != 0) {
            cout << "Reducere de 20% aplicata!\n";
            total = total * 0.8;
        }

        if (dynamic_cast<ClientNou*>(client.get())) {
            cout << "Reducere de 25% aplicata pentru clientul nou!\n";
            total = total * 0.75; // Reducere 25%
        }

        if (nrComenzi == 0) {
            cout << "Aplicam taxa de creare cont...\n";


            if (auto contStandard = dynamic_cast<ContStandard*>(client.get())) {
                total += contStandard->costlivrare();
                cout << "Taxa pentru ContStandard adaugata!\n";
            } else if (auto contPremium = dynamic_cast<ContPremium*>(client.get())) {
                total += contPremium->costlivrare();
                cout << "Taxa pentru ContPremium adaugata!\n";
            } else if (auto contVip = dynamic_cast<ContVip*>(client.get())) {
                total += contVip->costlivrare();
                cout << "Taxa pentru ContVIP adaugata!\n";
            } else {
                cout << "Tip de cont necunoscut!\n";
            }

        }

        Client::actualizeazaNRComanda(client->getId_Client());
    }

        cout<<"vasilica";
        cout << "Nr comenzi (): " << client->getNrComenzi() << endl;

    cout << "Total de plata: " << total << " lei\n";
}




    /*
    int cal(Cont * normal) {
        if(dynamic_cast<ContNormal*>(normal))
            cout<<functiecaluclarecalorii
        if(dynamic_cast<ContPremium*>(normal))
            cout<<functiecaluclarecalorii
    }#

    void afisarecal(Cont * c)
    {
        cout<<cal( c);
    }*/




    static void afiseazaTipMeniu() {
        cout << "\nAlege tipul de produs:\n";
        cout << "1. Mancare\n";
        cout << "2. Bauturi\n";
        cout << "3. Deserturi\n";
    }

    static void afiseazaOptiuni(bool& trecePeste) {
        cout << "ID invalid. Alegeti o optiune:\n";
        cout << "1. Creeaza un cont nou\n";
        cout << "2. Treci peste\n";
        cout << "3. Mai incearca\n";

        int optiune;
        cin >> optiune;

        switch (optiune) {
        case 1:
            creeazaContNou();
            break;

        case 2: {
            cout << "Comanda fara cont.\n";
            trecePeste = true;  // Permitem trecerea la comanda fără cont
            break;
        }
        case 3:
            cout << "Reincercati sa introduceti ID-ul.\n";
            break;
        default:
            cout << "Optiune invalida. Reincercati.\n";
        }
    }



    static void creeazaContNou() {
        ClientNou clientNou;
        clientNou.citesteDate();
        clientNou.salveazaInFisier("Clienti.txt");
        cout << "Client salvat cu succes!\n";

        cout << "ID-ul clientului: " << clientNou.getId_Client() << "\n";

        if (const auto& obiectiv = clientNou.getObiectiv()) {
            cout << "Obiectivul ales: " << obiectiv->getObiectivString() << "\n";

            int calorii = obiectiv->calculeazaCalorii(clientNou.getGreutate(), clientNou.getInaltime(), clientNou.getVarsta(), clientNou.getGen());
            cout << "Caloriile necesare: " << calorii << "\n";
        } else {
            cout << "Obiectivul nu a fost setat corect.\n";
        }

    }

};

/*

class InterfataUtilizator {
private:
    unique_ptr<Client> client;
    int calorii = 0;
    bool optiuneServireAleasa = false;
    ContVIP contvip;

public:
    InterfataUtilizator() : client(nullptr), contvip(0, "", "", "", Antrenor( "","",0)) {}

      void pornire() {
    unique_ptr<Client> client = nullptr;
    bool trecePeste = false;
    cout << "      Bine ati venit la HELLO FRESH!\n";
    cout << "     -------------------------------\n";

    while (true) {
        if (!trecePeste) {
            cout << "Introduceti ID-ul: ";
            int id;
            cin >> id;

            try {
                if (verificaId(id, client)) {
                    cout << "ID valid! Puteti comanda mancare.\n";

                    // verificam daca clientul are cont VIP (33) sau Premium (22)
                    if (id / 100 == 33 || id / 100 == 22) { // cont VIP sau Premium
                        int optiuneBox, generare;
                        cout << "Doriti sa comandati un plan alimentar (la pachet)? (1 - Da, 0 - Nu): ";
                        cin >> optiuneBox;
                        cout << "Doriti sa generam noi un meniu personalizat pentru dumneavoastra? (1-Da, 0-Nu): ";
                        cin >> generare;

                        if (optiuneBox == 1) {
                            int nrzile;
                            client->setOptiuneServire(LaPachet);
                            cout << "Pentru cate zile doriti planul alimentar: ";
                            cin >> nrzile; // citim numarul de zile

                            if (generare == 1) {
                                calorii = getCaloriiById(client->getId_Client());
                                PlanAlimentar plan(client->getId_Client(), calorii);
                                plan.construiesteMeniu(nrzile, false); // trimiterea numarului de zile
                                cout << "Comanda va ajunge in jurul orei 18:00 la adresa din cont.\n";
                            } else {
                                calorii = getCaloriiById(client->getId_Client());
                                PlanAlimentar plan(client->getId_Client(), calorii);
                                plan.construiesteMeniu(nrzile, true); // alegere manuala
                                cout << "---Comanda a fost plasata-----\n";
                                cout << "---Va ajunge in jurul orei 18:00 la adresa din cont";
                            }
                        }
                    }

                    // permite rezervarea mesei doar pentru cei cu cont VIP sau Premium
                    if (id / 100 == 33 || id / 100 == 22) { // VIP sau Premium
                        int optiuneServire;
                        cout << "Alege optiunea de servire:\n";
                        cout << "1. La restaurant (rezervare masa)\n";
                        cout << "2. La pachet\n";
                        cout << "Alegere: ";
                        cin >> optiuneServire;

                        try {
                            switch (optiuneServire) {
                            case 1: {
                                client->setOptiuneServire(InRestaurant);
                                if (id / 100 == 33) {  // cont VIP
                                    ContVIP::rezervaMasa(); // rezerva masa doar pentru cont VIP
                                }
                                break;
                            }
                            case 2:
                                client->setOptiuneServire(LaPachet);
                                break;
                            default:
                                throw ProdusInvalidException("Optiune invalida.");
                            }
                        } catch (const ProdusInvalidException& e) {
                            cout << e.what() << endl;
                            continue;
                        }
                    } else {
                        cout << "Nu aveti acces la rezervarea mesei.\n";
                    }

                    // continua comanda
                    MeniuPrincipal meniu;
                    afiseazaComanda(meniu, client);
                    break;
                } else {
                    afiseazaOptiuni(trecePeste);
                }
            } catch (const FisierException& e) {
                cout << "Eroare la citirea fisierului: " << e.what() << endl;
                break;
            }
        } else {
            // daca treci peste, creezi un client temporar
            client = make_unique<Client>(-1, "Client fara cont", "Necunoscut", "Necunoscut");
            MeniuPrincipal meniu;
            afiseazaComanda(meniu, client);
            break;
        }
    }
}


  static bool verificaId(int id, unique_ptr<Client>& client) {
          ifstream fisier("Clienti.txt");
          if (!fisier.is_open()) {
              throw FisierException("Nu s-a putut deschide fișierul Clienti.txt.");
          }

          string linie;
          while (getline(fisier, linie)) {
              if (linie.find("ID: ") == 0) {
                  int idFisier = stoi(linie.substr(4));
                  if (idFisier == id) {
                      string nume, telefon, adresa;
                      int nrComenzi = 0;  // Inițializăm nrComenzi
                      getline(fisier, linie);
                      if (linie.find("Nume: ") == 0) nume = linie.substr(6);
                      getline(fisier, linie);
                      if (linie.find("Telefon: ") == 0) telefon = linie.substr(9);
                      getline(fisier, linie);
                      if (linie.find("Adresa: ") == 0) adresa = linie.substr(8);
                      getline(fisier, linie);
                      if (linie.find("NrComenzi: ") == 0) nrComenzi = stoi(linie.substr(11));  // Citim nrComenzi

                      client = make_unique<Client>(idFisier, nume, telefon, adresa, nrComenzi);  // Creăm obiectul client cu nrComenzi
                      return true;
                  }
              }
          }

          return false;
      }


    static void afiseazaOptiuneServire(unique_ptr<Client>& client, InterfataUtilizator& interfata) {
        try {
            int optiuneServire;
            cout << "Alege optiunea de servire:\n";
            cout << "1. La restaurant\n";
            cout << "2. La pachet\n";
            cout << "Alegere: ";
            cin >> optiuneServire;

            switch (optiuneServire) {
                case 1:
                    client->setOptiuneServire(InRestaurant);
                if (client->getId_Client() / 100 == 33) { // verifica daca utilizatorul este VIP
                    ContVIP::rezervaMasa(); // acceseaza contvip prin obiectul InterfataUtilizator
                }
                break;
                case 2:
                    client->setOptiuneServire(LaPachet);
                break;
                default:
                    throw ProdusInvalidException("Optiune invalida.");
            }
        } catch (const ProdusInvalidException& e) {
            cout << e.what() << endl;
            afiseazaOptiuneServire(client, interfata);  // repetă alegerea dacă este invalidă
        }
    }



static void afiseazaComanda(MeniuPrincipal& meniu, const unique_ptr<Client>& client) {
    int optiune;
    bool continuare = true;
    vector<pair<unique_ptr<Produs>, int>> comanda;

   double total = 0;
    int nrComenzi = client->getNrComenzi();


    while (continuare) {
        afiseazaTipMeniu();
        cin >> optiune;

        switch (optiune) {
        case 1:
            meniu.citesteProduseDinFisier("meniu.txt");
            break;
        case 2:
            meniu.citesteProduseDinFisier("meniuBar");
            break;
        case 3:
            meniu.citesteProduseDinFisier("meniuDesert.txt");
            break;
        default:
            cout << "Optiune invalida. Te rog alege din nou.\n";
            continue;
        }

        meniu.afiseazaMeniu();

        cout << "Alege un produs (indice): ";
        int produsSelectat;
        cin >> produsSelectat;

        if (produsSelectat > 0 && produsSelectat <= meniu.getNrProduse()) {
            const auto& produs = meniu.getProduse()[produsSelectat - 1];
            cout << "Ai ales: " << produs->getNume() << "\n";

            int cantitate;
            cout << "Cate portii doresti? ";
            cin >> cantitate;

            comanda.emplace_back(produs->clone(), cantitate);
            cout << "Ai adaugat " << cantitate << " portii de " << produs->getNume() << "\n";
        }
        else {
            cout << "Index invalid!\n";
        }

        cout << "Vrei sa adaugi alt produs? (1 pentru da, 0 pentru nu): ";
        cin >> continuare;
    }

    cout << "\n--- Comanda Finala ---\n";
    if (client) {
        cout << "Client: " << client->getNume() << "\n";
        cout << "ID_CLIENT: " << client->getId_Client() << "\n";
        cout << "Telefon: " << client->getTelefon() << "\n";
        cout << "Adresa: " << client->getAdresa() << "\n";
    }
    else {
        cout << "Client:------\n";
    }

    // Adăugăm costul produselor la total
    for (const auto& [produs, cantitate] : comanda) {
        cout << "Produs: " << produs->getNume()
            << ", Cantitate: " << cantitate
            << ", Pret unitar: " << produs->getPret() << " lei\n";
        total += produs->getPret() * cantitate;
    }

    // Aplicăm reducerile
    if (client) {
        // Reducere de 20% pentru clienti cu numar de comenzi divizibil cu 5
        if (client->getNrComenzi() % 5 == 0 && client->getNrComenzi() != 0) {
            cout << "Reducere de 20% aplicata!\n";
            total = total * 0.8; // Reducere 20%
        }

        // Reducere de 25% pentru clientii noi
        if (dynamic_cast<ClientNou*>(client.get())) {
            cout << "Reducere de 25% aplicata pentru clientul nou!\n";
            total = total * 0.75; // Reducere 25%
        }

        if (nrComenzi == 0) {
            cout << "Aplicam taxa de creare cont...\n";

            // Verificăm ce tip de cont are clientul
            if (auto cont = dynamic_cast<Cont*>(client.get())) {
                // Dacă clientul este de tipul Cont sau un subtip al acestuia
                if (dynamic_cast<ContStandard*>(cont)) {
                    total += 12.0;  // Taxa pentru ContStandard
                    cout << "Taxa pentru ContStandard adaugata!\n";
                }
                else if (dynamic_cast<ContPremium*>(cont)) {
                    total += 20.0;  // Taxa pentru ContPremium
                    cout << "Taxa pentru ContPremium adaugata!\n";
                }
                else if (dynamic_cast<ContVIP*>(cont)) {
                    total += 30.0;  // Taxa pentru ContVIP
                    cout << "Taxa pentru ContVIP adaugata!\n";
                }
                else {
                    cout << "Tip de cont necunoscut!\n";
                }
            } else {
                cout << "Clientul nu are un cont valid!\n";
            }
        }

        Client::actualizeazaNRComanda(client->getId_Client());
    }

        cout<<"vasile";
        cout << "Nr comenzi (): " << client->getNrComenzi() << endl;

    cout << "Total de plata: " << total << " lei\n";
}




    static void afiseazaTipMeniu() {
        cout << "\nAlege tipul de produs:\n";
        cout << "1. Mancare\n";
        cout << "2. Bauturi\n";
        cout << "3. Deserturi\n";
    }

    static void afiseazaOptiuni(bool& trecePeste) {
        cout << "ID invalid. Alegeti o optiune:\n";
        cout << "1. Creeaza un cont nou\n";
        cout << "2. Treci peste\n";
        cout << "3. Mai incearca\n";

        int optiune;
        cin >> optiune;

        switch (optiune) {
        case 1:
            creeazaContNou();
            break;

        case 2: {
            cout << "Comanda fara cont.\n";
            trecePeste = true;  // Permitem trecerea la comanda fără cont
            break;
        }
        case 3:
            cout << "Reincercati sa introduceti ID-ul.\n";
            break;
        default:
            cout << "Optiune invalida. Reincercati.\n";
        }
    }


    static void creeazaContNou() {
        ClientNou clientNou;
        clientNou.citesteDate();
        clientNou.salveazaInFisier("Clienti.txt");
        cout << "Client salvat cu succes!\n";

        // Afișează ID-ul clientului
        cout << "ID-ul clientului: " << clientNou.getId_Client() << "\n";

        // Accesăm obiectivul clientului
        if (const auto& obiectiv = clientNou.getObiectiv()) {
            cout << "Obiectivul ales: " << obiectiv->getObiectivString() << "\n";

            // calculeaza  caloriile pentru obiectivul ales
            int calorii = obiectiv->calculeazaCalorii(clientNou.getGreutate(), clientNou.getInaltime(), clientNou.getVarsta(), clientNou.getGen());
            cout << "Caloriile necesare: " << calorii << "\n";
        } else {
            cout << "Obiectivul nu a fost setat corect.\n";
        }

    }


};*/



int main() {
    try {

        InterfataUtilizator interfata;

        // Apelăm metoda pornire care va gestiona interacțiunile utilizatorului
        interfata.pornire();
    }
    catch (const std::exception& e) {
        std::cerr << "A apărut o eroare: " << e.what() << std::endl;
    }
    return 0;
}


/*int main() {

    try {
        ClientNou client;

        // Citirea datelor de la utilizator
        client.citesteDate();

        // Dacă ai nevoie să salvezi clientul într-un fișier
        client.salveazaInFisier("clienti.txt");


    } catch (const ExceptieOptiuneInvalida& e) {
        std::cerr << "Eroare: " << e.what() << std::endl;
    } catch (const ExceptieFisier& e) {
        std::cerr << "Eroare la accesarea fisierului: " << e.what() << std::endl;
    }

    return 0;
}*/