#include "carretera.hpp"

Carretera::Carretera(sf::Texture& textura, sf::RenderWindow& window) : window(window), detenida(false) {
    sprite.setTexture(textura);
    sprite2.setTexture(textura);
    sprite2.setPosition(0, -sprite.getTexture()->getSize().y);
}

void Carretera::mover(float velocidad, const Carro& carro) {
    if (carro.getSprite().getPosition().x >= 100 && carro.getSprite().getPosition().x <= 700) {
        detener();
    }

    if (!detenida) {
        sprite.move(0, velocidad);
        sprite2.move(0, velocidad);

        if (sprite.getPosition().y >= window.getSize().y) {
            sprite.setPosition(0, sprite2.getPosition().y - sprite.getTexture()->getSize().y);
        }
        if (sprite2.getPosition().y >= window.getSize().y) {
            sprite2.setPosition(0, sprite.getPosition().y - sprite2.getTexture()->getSize().y);
        }
    }
}

void Carretera::dibujar() {
    window.draw(sprite);
    window.draw(sprite2);
}

bool Carretera::estaDetenida() const {
    return detenida;
}

void Carretera::detener() {
    detenida = true;
}

void Carretera::reanudar() {
    detenida = false;
}
