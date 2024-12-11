#include "carro.hpp"

Carro::Carro(sf::Texture& textura, float posicionInicialX, float posicionInicialY) {
    sprite.setTexture(textura);
    sprite.setPosition(posicionInicialX, posicionInicialY);

    rangoMinX = 100.0f;
    rangoMaxX = 700.0f;
    posicionYConstante = posicionInicialY;

    sf::Texture texturaMensaje;
    if (!texturaMensaje.loadFromFile("./assets/images/game over.png")) {
        std::cerr << "Error al cargar la textura del mensaje de pérdida" << std::endl;
    }
    mensajePerdida.setTexture(texturaMensaje);
    mensajePerdida.setPosition(300, 250);
}

void Carro::mover(float velocidad, sf::Keyboard::Key A, sf::Keyboard::Key D) {
    if (sf::Keyboard::isKeyPressed(A)) {
        sprite.move(-velocidad, 0);
    }
    if (sf::Keyboard::isKeyPressed(D)) {
        sprite.move(velocidad, 0);
    }
}

bool Carro::verificarSalidaRango() const {
    return (sprite.getPosition().x < rangoMinX || sprite.getPosition().x > rangoMaxX);
}

void Carro::dibujar(sf::RenderWindow& window) {
    if (verificarSalidaRango()) {
        window.draw(mensajePerdida);
    } else {
        window.draw(sprite);
    }
}

sf::Sprite Carro::getSprite() const {
    return sprite;
}

sf::FloatRect Carro::getBounds() const {
    return sprite.getGlobalBounds();
}
