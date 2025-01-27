// Obiectiv.h
#ifndef OBIECTIV_H
#define OBIECTIV_H

#include <string>

class Obiectiv {
public:
    virtual ~Obiectiv() = default;
    virtual std::string getObiectivString() const = 0;
    virtual int calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const = 0;

protected:
    void valideaza(int greutate, int inaltime, int varsta, int gen) const;
    void valideazaDate(int greutate, int inaltime, int varsta, int gen)  const ;
};

class Slabire : public Obiectiv {
public:
    std::string getObiectivString() const override;
    int calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const override;
};

class MasaMusculara : public Obiectiv {
public:
    std::string getObiectivString() const override;
    int calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const override;
};

class Mentinere : public Obiectiv {
public:
    std::string getObiectivString() const override;
    int calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const override;
};

class Definire : public Obiectiv {
public:
    std::string getObiectivString() const override;
    int calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const override;
};

#endif // OBIECTIV_H
