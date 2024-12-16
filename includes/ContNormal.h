#ifndef CONTNORMAL_H
#define CONTNORMAL_H

#include "Cont.h"


class ContNormal : public Cont {
public:
    ContNormal(int id_client, const std::string& nume, const std::string& telefon, const std::string& adresa);
    double costlivrare() override;
    [[nodiscard]] std::unique_ptr<Cont> clone() const override;
};

#endif // CONTNORMAL_H
