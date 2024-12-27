#ifndef CRESTERE_PERFORMANTA_H
#define CRESTERE_PERFORMANTA_H

#include "Obiectiv.h"
#include <string>

class CresterePerformanta : public Obiectiv {
public:
    CresterePerformanta() = default;
    ~CresterePerformanta() override = default;

    [[nodiscard]] std::string getObiectivString() const override;

    [[nodiscard]] static int calculeazaCalorii(int greutate,  int varsta, int gen) ;
};

#endif // CRESTERE_PERFORMANTA_H
