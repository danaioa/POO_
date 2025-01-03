#include "Obiectiv.h"
#include "ObiectivFactory.h"
#include "CresterePerformanta.h"
#include "Exceptii.h"
#include <memory>

std::unique_ptr<Obiectiv> ObiectivFactory::creareObiectiv(const std::string& tipObiectiv) {
    if (tipObiectiv == "Slabire") {
        return std::make_unique<Slabire>();
    } else if (tipObiectiv == "MasaMusculara") {
        return std::make_unique<MasaMusculara>();
    } else if (tipObiectiv == "Mentinere") {
        return std::make_unique<Mentinere>();
    } else if (tipObiectiv == "CresterePerformanta") {
        return std::make_unique<CresterePerformanta>();
    } else {
        return nullptr;
    }
}

Obiectiv* ObiectivFactory::creareObiectivDupaOptiune(int optiune) {
    std::string tipObiectiv;
    switch (optiune) {
        case 1:
            tipObiectiv = "Slabire";
        break;
        case 2:
            tipObiectiv = "MasaMusculara";
        break;
        case 3:
            tipObiectiv = "Mentinere";
        break;
        case 4:
            tipObiectiv = "CresterePerformanta";
        break;
        default:
            throw ExceptieOptiuneInvalida();
    }

    return creareObiectiv(tipObiectiv).release();
}
