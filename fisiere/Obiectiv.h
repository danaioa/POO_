#ifndef OBIECTIV_H
#define OBIECTIV_H

#include <string>

class Obiectiv {
public:
    void valideaza(int greutate, int inaltime, int varsta, int gen) const;

protected:
    static void valideazaDate(int greutate, int inaltime, int varsta, int gen);

public:
    [[nodiscard]] virtual std::string getObiectivString() const = 0;
    [[nodiscard]] virtual int calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const = 0;
};


class Slabire : public Obiectiv {
public:
    [[nodiscard]] std::string getObiectivString() const override;
    [[nodiscard]] int calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const override;
};


class MasaMusculara : public Obiectiv {
public:
    [[nodiscard]] std::string getObiectivString() const override;
    [[nodiscard]] int calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const override;
};


class Mentinere : public Obiectiv {
public:
    [[nodiscard]] std::string getObiectivString() const override;
    [[nodiscard]] int calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const override;
};


class Definire : public Obiectiv {
public:
    [[nodiscard]] std::string getObiectivString() const override;
    [[nodiscard]] int calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const override;
};

#endif // OBIECTIV_H
