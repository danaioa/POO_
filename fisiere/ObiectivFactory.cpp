#include "Obiectiv.h"
#include "ObiectivFactory.h"
#include "CresterePerformanta.h"
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