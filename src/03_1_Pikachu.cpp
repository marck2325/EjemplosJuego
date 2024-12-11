#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 700;
const float CAR_SPEED = 0.2f;
float ROAD_SPEED = 0.001f;
const float ROAD_ACCELERATION = 0.00001f; 

float tiempoCuentaAtras = 3.0f;

bool checkCollision(sf::Sprite& sprite, sf::RectangleShape& obstacle) {
    return sprite.getGlobalBounds().intersects(obstacle.getGlobalBounds());
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Turbo racing");

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
    sf::Texture textureNumero3;
if (!textureNumero3.loadFromFile("./assets/images/3.png")) {
    std::cerr << "Error al cargar la textura del número 3" << std::endl;
    return 1;
}
sf::Sprite spriteNumero3(textureNumero3);
spriteNumero3.setPosition(WINDOW_WIDTH / 2 - spriteNumero3.getTextureRect().width / 2, WINDOW_HEIGHT / 2 - spriteNumero3.getTextureRect().height / 2);


    // Variables de desplazamiento
    float velocidadDesplazamiento = 0.1f;

    // Crear obstáculos
    std::vector<sf::RectangleShape> obstacles;
    sf::RectangleShape collisionZone1;
    collisionZone1.setPosition(0, 500);
    collisionZone1.setSize(sf::Vector2f(150, 50));
    obstacles.push_back(collisionZone1);

    // Nueva zona de colisión a la derecha
    sf::RectangleShape collisionZone2;
    collisionZone2.setPosition(WINDOW_WIDTH - 100, 500);
    collisionZone2.setSize(sf::Vector2f(150, 50));
    obstacles.push_back(collisionZone2);

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
         if (tiempoCuentaAtras > 0) {
        tiempoCuentaAtras -= 1.0f / 60.0f; // Ajustar el tiempo según la tasa de refresco
        window.draw(3);
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
        //window.draw(3);
        window.draw(spriteCarretera);
        window.draw(spriteCarretera2);
        window.draw(sprite);
        window.draw(collisionZone1);
        window.draw(collisionZone2);
        //window.draw(3);
        window.display();
    }

    return 0;
}