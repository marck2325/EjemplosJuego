#ifndef ROJO_HPP
#define ROJO_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Rojo
{
private:
    sf::Sprite sprite;
    float speed;

public:
    Rojo(const sf::Texture &texture, float initialX, float initialY, float speed);

    void update(float deltaTime);
    void draw(sf::RenderWindow &window);
    const sf::Sprite &getSprite() const;
};

#endif // ROJO_HPP