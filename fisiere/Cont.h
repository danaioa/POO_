#ifndef CONT_H
#define CONT_H

#include <memory>
#include <string>
#include "Client.h"

class Cont {
protected:
    std::unique_ptr<Client> client;
    int PretCont;

public:
    Cont(int id_client, const std::string& nume, const std::string& telefon, const std::string& adresa,
         int nrComenzi = 0, OptiuneServire optiune = OptiuneServire::InRestaurant, int pret = 0);

    Cont(Cont&& other) noexcept;

    virtual ~Cont() = default;

    virtual double costlivrare() = 0;

    void salveazaInFisier() const;

    static int citesteUltimulNumar(const std::string& filename, int prefix);

    static int generareCod(int prefix);

    [[nodiscard]] virtual std::unique_ptr<Cont> clone() const=0;
};

#endif // CONT_H
