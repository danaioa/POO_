#ifndef CARACTERE_H
#define CARACTERE_H

#include <SFML/Graphics.hpp>

class PersonajPrincipal {
private:
    sf::Texture textura;
    sf::Sprite sprite;
    sf::Vector2f pozitie;
    sf::IntRect cadruCurent; // Reprezintă secțiunea selectată din sprite sheet
    float viteza;
    const int latimeCadru = 300;  // Lățimea unui cadru
    const int inaltimeCadru = 300; // Înălțimea unui cadru

public:
    // Constructor
    PersonajPrincipal(const sf::Vector2f& poz = {100.0f, 300.0f}, float vit = 0.2f, const std::string& caleTextura = "textures/personaj.png")
        : pozitie(poz), viteza(vit) {
        if (!textura.loadFromFile(caleTextura)) {
            throw std::runtime_error("Nu s-a putut încărca textura!");
        }
        sprite.setTexture(textura);

        // Dimensiunea unui singur cadru (ajustată pentru sprite sheet)
        cadruCurent = sf::IntRect(0, 0, latimeCadru, inaltimeCadru); // (x, y, lățime, înălțime)
        sprite.setTextureRect(cadruCurent);
        sprite.setPosition(pozitie);
    }

    void schimbaCadru(int rand) {
        // Schimbă rândul din sprite sheet (sus/jos/stânga/dreapta)
        cadruCurent.top = rand * inaltimeCadru; // Fiecare rând are înălțimea de 64 px
        cadruCurent.left = 0;                  // Resetăm coloana la primul cadru
        sprite.setTextureRect(cadruCurent);
    }

    void actualizeazaPozitia(const sf::Vector2f& directie) {
        pozitie += directie * viteza;
        sprite.setPosition(pozitie);
    }

    void deseneaza(sf::RenderWindow& window) {
        window.draw(sprite);
    }
};

#endif // CARACTERE_H
