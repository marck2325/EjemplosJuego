#ifndef CARRO_H
#define CARRO_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Carro {
public:
    Carro(sf::Texture& textura, float posicionInicialX, float posicionInicialY);
    void mover(float velocidad, sf::Keyboard::Key A, sf::Keyboard::Key D);
    bool verificarSalidaRango() const;
    void dibujar(sf::RenderWindow& window);
    sf::Sprite getSprite() const;
    sf::FloatRect getBounds() const;

private:
    sf::Sprite sprite;
    sf::Sprite mensajePerdida;
    float rangoMinX;
    float rangoMaxX;
    float posicionYConstante;
};

#endif
