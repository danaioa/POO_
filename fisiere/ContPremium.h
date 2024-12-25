#ifndef CONTPREMIUM_H
#define CONTPREMIUM_H

#include "Cont.h"
#include "Obiectiv.h"
#include "Client.h"
#include <memory>

class ContPremium : public Cont {
    static constexpr double costCont = 20.0;
    Obiectiv* obiectiv;
    std::unique_ptr<Client> client;
    int greutate;
    int inaltime;
    int varsta;
    int gen;

public:
    explicit ContPremium(std::unique_ptr<Client> clientPtr);
    explicit ContPremium(int id, const std::string& nume, const std::string& telefon, const std::string& adresa);
    ~ContPremium() override;

    static double getCostCont();
    double costlivrare() override;
    void setObiectiv(Obiectiv* obj);
    static Obiectiv* alegeObiectiv();
    [[nodiscard]] std::unique_ptr<Cont> clone() const override;
    //void setDetaliiUtilizator(int greutate_, int inaltime_, int varsta_, int gen_);
    //void genereazaPlanAlimentar() const;
    static void rezervaMasa();
    static std::string trim(const std::string& str);
    static int getCaloriiById(int id);
};

#endif
