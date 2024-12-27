#ifndef CRESTERE_PERFORMANTA_H
#define CRESTERE_PERFORMANTA_H

#include "Obiectiv.h"
#include <string>

class CresterePerformanta : public Obiectiv {
public:
    CresterePerformanta() = default;
    ~CresterePerformanta() override = default;

    [[nodiscard]] std::string getObiectivString() const override;

    [[nodiscard]] int calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const override;
};

#endif // CRESTERE_PERFORMANTA_H
