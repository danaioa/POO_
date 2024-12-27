#include "CresterePerformanta.h"


std::string CresterePerformanta::getObiectivString() const {
    return "Crestere Performanta";
}

int CresterePerformanta::calculeazaCalorii(int greutate,int varsta, int gen) {
    if (gen == 1) {
        return (greutate * 15) - (varsta * 10);
    } else {
        return (greutate * 12) - (varsta * 9);
    }
}
