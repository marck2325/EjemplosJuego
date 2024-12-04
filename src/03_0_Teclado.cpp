#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 700;
const float CAR_SPEED = 0.2f;
float ROAD_SPEED = 0.00001f;
const float ROAD_ACCELERATION = 0.00001f; 

bool checkCollision(sf::Sprite& sprite, sf::RectangleShape& obstacle) {
    return sprite.getGlobalBounds().intersects(obstacle.getGlobalBounds());
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Turbo rac");

    // Cargar texturas y crear sprites
    sf::Texture texturaCarretera;
    if (!texturaCarretera.loadFromFile("./assets/images/carretera.png")) {
        std::cerr << "Error al cargar la textura de la carretera" << std::endl;
        return 1;
    }
    sf::Sprite spriteCarretera(texturaCarretera);

    sf::Texture texture;
    if (!texture.loadFromFile("./assets/images/pixel_racecar_orange.png")) {
        std::cerr << "Error al cargar la textura del carro" << std::endl;
        return 1;
    }
    sf::Sprite sprite(texture);
    sprite.setPosition(400, 500);

    // Variables de desplazamiento
    float velocidadDesplazamiento = 0.1f;

    // Crear obstáculos
    std::vector<sf::RectangleShape> obstacles;
    sf::RectangleShape collisionZone;
    collisionZone.setPosition(0, 500);
    collisionZone.setSize(sf::Vector2f(175, 50));
    obstacles.push_back(collisionZone);

    // Posicionar la segunda carretera para crear un fondo infinito
    sf::Sprite spriteCarretera2(texturaCarretera);
    spriteCarretera2.setPosition(0, -spriteCarretera.getTextureRect().height);

    // Bucle principal
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Comprobación de colisiones
        for (auto& obstacle : obstacles) {
            if (checkCollision(sprite, obstacle)) {
                std::cout << "¡Colisión!" << std::endl;
            }
        }

        // Control de movimiento del carro
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            sprite.move(-CAR_SPEED, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            sprite.move(CAR_SPEED, 0);
        }
        ROAD_SPEED += ROAD_ACCELERATION;
        // Mover la carretera
        spriteCarretera.move(0, ROAD_SPEED);
        spriteCarretera2.move(0, ROAD_SPEED);

        // Comprobar si la carretera ha salido de la pantalla y reposicionarla para que se vea infinita
        if (spriteCarretera.getPosition().y > window.getSize().y) {
            spriteCarretera.setPosition(0, -spriteCarretera.getTextureRect().height);
        }
        if (spriteCarretera2.getPosition().y > window.getSize().y) {
            spriteCarretera2.setPosition(0, -spriteCarretera2.getTextureRect().height);
        }

        // Dibujar en la ventana
        //window.draw(spriteCarretera);
       //window.clear();
       //window.draw(spriteCarretera);
        window.draw(spriteCarretera);
        window.draw(spriteCarretera2);
        window.draw(spriteCarretera);
        window.draw(sprite);
        //window.draw(spriteCarretera);
      //  window.draw(collisionZone);
        window.display();
    }

    return 0;
}

