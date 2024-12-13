#include "rojo.hpp"

Rojo::Rojo(const sf::Texture& texture, float initialX, float initialY, float speed)
    : speed(speed) {
    sprite.setTexture(texture);
    sprite.setPosition(initialX, initialY);
}

void Rojo::update(float deltaTime) {
    sprite.move(0, speed * deltaTime);
    if (sprite.getPosition().y > 600) {
        sprite.setPosition(static_cast<float>(rand() % 800), -100);
    }
}

void Rojo::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

const sf::Sprite& Rojo::getSprite() const {
    return sprite;
}