#ifndef CALCULEAZA_NIVELUL_STRESULUI_H
#define CALCULEAZA_NIVELUL_STRESULUI_H

#include <iostream>
using namespace std;

template <typename T>
class CalculeazaNivelulStresului {
private:
    T numarExamene;
    T zilePanaPrimulExamen;
    T zilePanaUltimulExamen;
    int nivelStres; // 1 - Mic, 2 - Mediu, 3 - Mare

public:
    CalculeazaNivelulStresului()
        : numarExamene(0), zilePanaPrimulExamen(0), zilePanaUltimulExamen(0), nivelStres(0) {}

    void citesteDate() {
        cout << "Introduceti numarul de examene: ";
        cin >> numarExamene;
        cout << "Introduceti numarul de zile pana la primul examen: ";
        cin >> zilePanaPrimulExamen;
        cout << "Introduceti numarul de zile pana la ultimul examen: ";
        cin >> zilePanaUltimulExamen;
        cout << "Alegeti nivelul de stres (1 - Mic, 2 - Mediu, 3 - Mare): ";
        cin >> nivelStres;
    }

    void calul() {
        T scorStres = (numarExamene * 10) - (zilePanaPrimulExamen * 2) + (zilePanaUltimulExamen * 1);

        cout << "Scorul de stres calculat: " << scorStres << endl;

        if (scorStres < 30) {
            cout << "Nivel de stres: Mic (Recomandare: Relaxeaza-te si organizeaza-te!)" << endl;
        } else if (scorStres >= 30 && scorStres <= 60) {
            cout << "Nivel de stres: Mediu (Recomandare: Fii concentrat si planifica-ti timpul!)" << endl;
        } else {
            cout << "Nivel de stres: Mare (Recomandare: Ia o pauza si incearca sa-ti controlezi emotiile!)" << endl;
        }
    }

};

#endif
