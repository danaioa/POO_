#ifndef OBIECTIV_FACTORY_H
#define OBIECTIV_FACTORY_H

#include "Obiectiv.h"
#include <memory>

class ObiectivFactory {
public:
    static std::unique_ptr<Obiectiv> creareObiectiv(const std::string& tipObiectiv);
};

#endif // OBIECTIV_FACTORY_H
