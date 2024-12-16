#ifndef OBIECTIV_H
#define OBIECTIV_H

#include <string>

using std::string;


class Obiectiv {
public:
    virtual ~Obiectiv() = default;


    [[nodiscard]] virtual string getObiectivString() const = 0;


    [[nodiscard]] virtual int calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const = 0;
};


class Slabire : public Obiectiv {
public:
    [[nodiscard]] string getObiectivString() const override;
    [[nodiscard]] int calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const override;
};


class MasaMusculara : public Obiectiv {
public:
    [[nodiscard]] string getObiectivString() const override;
    [[nodiscard]] int calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const override;
};


class Mentinere : public Obiectiv {
public:
    [[nodiscard]] string getObiectivString() const override;
    [[nodiscard]] int calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const override;
};

#endif // OBIECTIV_H
