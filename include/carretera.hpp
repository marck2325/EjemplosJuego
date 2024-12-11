#ifndef CARRETERA_H
#define CARRETERA_H

#include <SFML/Graphics.hpp>
#include "carro.hpp"

class Carretera {
public:
    Carretera(sf::Texture& textura, sf::RenderWindow& window);
    void mover(float velocidad, const Carro& carro);
    void dibujar();
    bool estaDetenida() const;
    void detener();
    void reanudar();

private:
    sf::Sprite sprite;
    sf::Sprite sprite2;
    sf::RenderWindow& window;
    bool detenida;
};

#endif
