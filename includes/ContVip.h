

#ifndef CONTVIP_H
#define CONTVIP_H

#include "Cont.h"
#include "Client.h"
#include "Antrenor.h"
#include "Obiectiv.h"
#include "Sport.h"
#include <memory>

class ContVip : public Cont {
    std::unique_ptr<Client> client;
    static constexpr double costCont = 20.5;
    Obiectiv* obiectiv{};
    Sport sportAles;
    int greutate{};
    int inaltime{};
    int varsta{};
    int gen{};
    Antrenor antrenorAles;
    std::string oraAleasaFinala;
    std::string ziAleasaFinala;

public:
    ContVip(int id_client, const std::string& nume, const std::string& telefon, const std::string& adresa,
            int nrComenzi = 0, OptiuneServire optiune = OptiuneServire::InRestaurant, int pret = 0);

    static double getCostCont();
    void setDetaliiUtilizator(int greutate_, int inaltime_, int varsta_, int gen_);
    double costlivrare() override;
    void setObiectiv(Obiectiv* obj);
    static Obiectiv* alegeObiectiv();
    [[nodiscard]] int calculeazaNecesarCaloric() const;
    void genereazaPlanAlimentar() const;
    static void rezervaMasa();
    void alegeSport();
    [[nodiscard]] std::string getSportString() const;
    void alegeAntrenor();
    void alegeZiSiOra();
    void verificaLocuriDisponibile() const;
    [[nodiscard]] std::unique_ptr<Cont> clone() const override;
    static std::string trim(const std::string& str);
    static int getCaloriiById(int id);

};

#endif
