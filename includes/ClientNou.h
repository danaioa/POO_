#ifndef CLIENT_NOU_H
#define CLIENT_NOU_H


#include <string>
#include <memory>
#include "Client.h"
#include "ContVip.h"
#include "Obiectiv.h"


using namespace std;

enum OptiuneCont { Normal, Standard, Premium, VIP };

class ClientNou : public Client {
    unique_ptr<Obiectiv> obiectiv;
    OptiuneCont tipCont;
    int calorizilnice = 0;
    Sport sportAles;
    string dataExpirareAbonament;
    int caloriiZilnice{};

public:
    ClientNou(int id, const std::string& nume, const std::string& telefon, const std::string& adresa);
    ClientNou();

    [[nodiscard]] const unique_ptr<Obiectiv>& getObiectiv() const;
    void setDataExpirare(int luni);
    void citesteDate();
    void salveazaInFisier(const string& fisier) const;
};

#endif // CLIENT_NOU_H
