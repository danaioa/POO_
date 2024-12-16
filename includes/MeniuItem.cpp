#include "MeniuItem.h"

MeniuItem::MeniuItem(std::string n, int c, float p, std::string cat)
    : nume(std::move(n)), calorii(c), pret(p), categorie(std::move(cat)) {}
