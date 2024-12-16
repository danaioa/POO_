#ifndef CONTSTANDARD_H
#define CONTSTANDARD_H

#include "Cont.h"

class ContStandard : public Cont {
    static constexpr double costCont = 15.5;
public:
    ContStandard(int id_client, const std::string& nume, const std::string& telefon, const std::string& adresa);
    static double getCostCont();
    double costlivrare() override;
    [[nodiscard]] std::unique_ptr<Cont> clone() const override;
};

#endif // CONTSTANDARD_H
