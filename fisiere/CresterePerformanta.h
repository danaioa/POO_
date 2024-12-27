#ifndef CRESTEREPERFORMANTA_H
#define CRESTEREPERFORMANTA_H

#include "Obiectiv.h"
#include <string>

class CresterePerformanta : public Obiectiv {
public:
    [[nodiscard]] std::string getObiectivString() const override;

    [[nodiscard]] int calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const override;
};

#endif // CRESTEREPERFORMANTA_H
