#include "MeniuItem.h"
#include <utility>

MeniuItem::MeniuItem(std::string n, int c, float p, std::string cat)
    : nume(std::move(n)), calorii(c), pret(p), categorie(std::move(cat)) {}

MeniuItem::MeniuItem(MeniuItem&& other) noexcept
    : nume(std::move(other.nume)), calorii(other.calorii), pret(other.pret), categorie(std::move(other.categorie)) {}

MeniuItem& MeniuItem::operator=(MeniuItem&& other) noexcept {
    if (this != &other) {
        nume = std::move(other.nume);
        calorii = other.calorii;
        pret = other.pret;
        categorie = std::move(other.categorie);
    }
    return *this;
}



void swap(MeniuItem& a, MeniuItem& b) noexcept{
    using std::swap;
    swap(a.nume, b.nume);
    swap(a.calorii, b.calorii);
    swap(a.pret, b.pret);
    swap(a.categorie, b.categorie);
}