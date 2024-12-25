#ifndef CLIENT_H
#define CLIENT_H
#include "OptiuneServire.h"
#include <string>



class Client {
protected:
    std::string Nume;
    std::string Telefon;
    std::string Adresa;
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
    Client(int id, std::string nume, std::string telefon, std::string adresa, int nrComenzi = 0, OptiuneServire optiune = OptiuneServire::InRestaurant);
    virtual ~Client() = default;

    Client& operator=(Client other);

    [[nodiscard]] int getPret() const;
    void setPret(double cost);
    [[nodiscard]] int getVarsta() const;
    [[nodiscard]] const std::string& getNume() const;
    [[nodiscard]] const std::string& getTelefon() const;
    [[nodiscard]] const std::string& getAdresa() const;
    [[nodiscard]] int getGen() const;
    [[nodiscard]] int getInaltime() const;
    [[nodiscard]] int getGreutate() const;
    [[nodiscard]] int getId_Client() const;
    [[nodiscard]] int getNrComenzi() const;
    [[nodiscard]] OptiuneServire getOptiuneServire() const;

   [[maybe_unused]] void setNume(const std::string& nume);
   [[maybe_unused]] void setTelefon(const std::string& telefon);
    [[maybe_unused]] void setAdresa(const std::string& adresa);
    void setOptiuneServire(OptiuneServire optiune);

    static void actualizeazaNRComanda(int id);
    static int citesteUltimulNumar(const std::string& filename);
    static int generareCod();
};

#endif // CLIENT_H
