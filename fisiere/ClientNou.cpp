#include "ClientNou.h"
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <memory>
#include "Client.h"
#include "ContNormal.h"
#include "ContStandard.h"
#include "ContPremium.h"
#include "ContVip.h"
#include "Obiectiv.h"
#include "Antrenor.h"
#include "Exceptii.h"


ClientNou::ClientNou(int id, const std::string& nume, const std::string& telefon, const std::string& adresa)
    : Client(id, nume, telefon, adresa), tipCont(Normal), sportAles(Sport::Sala) {}

ClientNou::ClientNou()
    : Client(-1, "Necunoscut", "Necunoscut", "Necunoscut"), tipCont(Normal), sportAles(Sport::Sala) {}

const unique_ptr<Obiectiv>& ClientNou::getObiectiv() const {
    return obiectiv;
}

void ClientNou::setDataExpirare(int luni) {
    time_t now = time(nullptr);
    tm* localtm = localtime(&now);
    localtm->tm_mon += luni;  // adaugă luni la data curentă
    mktime(localtm);  // normalizează structura tm
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d-%m-%Y", localtm);
    dataExpirareAbonament = string(buffer);
}

void ClientNou::citesteDate() {
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
        setDataExpirare(1);
    }
    else if (optiuneCont == 2) {
        tipCont = OptiuneCont::Standard;
        ContNormal contStandard(0, Nume, Telefon, Adresa);
        Id_Client = ContNormal::generareCod(22);
        cout << "       Costul contului standard: " << ContStandard::getCostCont() << endl;
        setPret(ContStandard::getCostCont());
        setDataExpirare(1);
    }
    else if (optiuneCont == 3) {
        tipCont = OptiuneCont::Premium;
        ContPremium contPremium(0, Nume, Telefon, Adresa);
        setPret(ContPremium::getCostCont());

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
        setPret(ContVip::getCostCont());
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
        }
        catch (const exception& e) {
            cout << "Eroare: " << e.what() << endl;
            caloriiZilnice = 0;
        }

        setDataExpirare(1);
    }
}

void ClientNou::salveazaInFisier(const string& fisier) const {
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
        << "NrComenzi: " << "0\n"
        << "Gen: " << (gen == 1 ? "Masculin" : "Feminin") << "\n";

    if (caloriiZilnice > 0) {
        out << "Calorii: " << caloriiZilnice << "\n";
    } else {
        out << "Calorii: -\n";
    }

    out << "Data expirare abonament: " << dataExpirareAbonament << "\n";
    out << "---------------------------\n";

    cout << "\nClientul a fost inregistrat cu succes! ID-ul clientului este: " << Id_Client << "\n";
}
