#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

class Carro {
private:
    sf::Sprite sprite;
    float x;
    float speed;

public:
    Carro(const sf::Texture& texture, float startX, float startY, float speed)
        : x(startX), speed(speed) {
        sprite.setTexture(texture);
        sprite.setPosition(startX, startY);
    }

    void moveLeft(float deltaTime) {
        x -= speed * deltaTime;
        if (x < 118) x = 118; // Limitar el movimiento en X
        sprite.setPosition(x, sprite.getPosition().y);
    }

    void moveRight(float deltaTime) {
        x += speed * deltaTime;
        if (x > 670) x = 670; // Limitar el movimiento en X
        sprite.setPosition(x, sprite.getPosition().y);
    }

    const sf::Sprite& getSprite() const { return sprite; }

    void resetPosition() {
        x = 400;
        sprite.setPosition(x, 500);
    }
};

class Objeto {
private:
    sf::Sprite sprite;
    float speed;

public:
    Objeto(const sf::Texture& texture, float startX, float startY, float speed)
        : speed(speed) {
        sprite.setTexture(texture);
        sprite.setPosition(startX, startY);
    }

    void update(float deltaTime) {
        sprite.move(0, speed * deltaTime);
        if (sprite.getPosition().y > 600) {
            sprite.setPosition(static_cast<float>(rand() % 552 + 118), -50);
        }
    }

    const sf::Sprite& getSprite() const { return sprite; }

    void resetPosition() {
        sprite.setPosition(static_cast<float>(rand() % 552 + 118), -50);
    }
};

void showCountdown(sf::RenderWindow& window, sf::Font& font) {
    sf::Text countdownText;
    countdownText.setFont(font);
    countdownText.setCharacterSize(50);
    countdownText.setFillColor(sf::Color::Red);
    countdownText.setPosition(350, 250);

    std::vector<std::string> countdown = {"3", "2", "1", "Ready Go!"};

    for (const auto& text : countdown) {
        countdownText.setString(text);
        window.clear();
        window.draw(countdownText);
        window.display();
        sf::sleep(sf::seconds(1));
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Car Game");
    sf::Texture playerTexture, greenBarrelTexture, blueBarrelTexture, redCarTexture, roadTexture;
    sf::RectangleShape background(sf::Vector2f(800, 600));
    background.setFillColor(sf::Color(50, 50, 50));

    // Cargar texturas
    if (!playerTexture.loadFromFile("./assets/images/pixel_racecar_orange.png") ||
        !greenBarrelTexture.loadFromFile("./assets/images/bidon.png") ||
        !blueBarrelTexture.loadFromFile("./assets/images/pixel_racecar_blue.png") ||
        !redCarTexture.loadFromFile("./assets/images/pixel_racecar.png") ||
        !roadTexture.loadFromFile("./assets/images/carretera.png")) {
        std::cerr << "Error loading textures" << std::endl;
        return -1;
    }

    Carro player(playerTexture, 400, 500, 300.0f);

    std::vector<Objeto> greenBarrels;
    std::vector<Objeto> blueBarrels;
    std::vector<Objeto> redCars;

    // Inicializar objetos
    for (int i = 0; i < 3; ++i) {
        greenBarrels.emplace_back(greenBarrelTexture, static_cast<float>(rand() % 600 + 100), -50, 150.0f);
        blueBarrels.emplace_back(blueBarrelTexture, static_cast<float>(rand() % 600 + 100), -50, 150.0f);
        redCars.emplace_back(redCarTexture, static_cast<float>(rand() % 600 + 100), -50, 200.0f);
    }

    int score = 0;
    sf::Font font;
    if (!font.loadFromFile("./assets/fonts/Minecraft.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return -1;
    }

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(10, 10);

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(200, 250);
    gameOverText.setString("Game Over! \n \n \n R para reiniciar");

    sf::Clock clock;
    bool isGameOver = false;

    showCountdown(window, font);

    sf::Sprite roadSprite1, roadSprite2;
    roadSprite1.setTexture(roadTexture);
    roadSprite2.setTexture(roadTexture);
    roadSprite1.setPosition(0, 0);
    roadSprite2.setPosition(0, -static_cast<float>(roadTexture.getSize().y));

    float roadSpeed = 400.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (isGameOver && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                // Reiniciar juego
                isGameOver = false;
                score = 0;
                player.resetPosition();

                for (auto& barrel : greenBarrels) {
                    barrel.resetPosition();
                }
                for (auto& barrel : blueBarrels) {
                    barrel.resetPosition();
                }
                for (auto& car : redCars) {
                    car.resetPosition();
                }

                roadSprite1.setPosition(0, 0);
                roadSprite2.setPosition(0, -static_cast<float>(roadTexture.getSize().y));
                showCountdown(window, font);
            }
        }

        if (isGameOver) {
            window.clear();
            window.draw(gameOverText);
            window.display();
            continue;
        }

        float deltaTime = clock.restart().asSeconds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player.moveLeft(deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player.moveRight(deltaTime);
        }

        for (auto& barrel : greenBarrels) {
            barrel.update(deltaTime);
            if (player.getSprite().getGlobalBounds().intersects(barrel.getSprite().getGlobalBounds())) {
                score += 20;
                barrel.resetPosition();
            }
        }

        for (auto& barrel : blueBarrels) {
            barrel.update(deltaTime);
            if (player.getSprite().getGlobalBounds().intersects(barrel.getSprite().getGlobalBounds())) {
                score -= 20;
                barrel.resetPosition();
            }
        }

        for (auto& car : redCars) {
            car.update(deltaTime);
            if (player.getSprite().getGlobalBounds().intersects(car.getSprite().getGlobalBounds())) {
                isGameOver = true;
            }
        }

        roadSprite1.move(0, roadSpeed * deltaTime);
        roadSprite2.move(0, roadSpeed * deltaTime);

        if (roadSprite1.getPosition().y >= 600) {
            roadSprite1.setPosition(0, roadSprite2.getPosition().y - roadTexture.getSize().y);
        }
        if (roadSprite2.getPosition().y >= 600) {
            roadSprite2.setPosition(0, roadSprite1.getPosition().y - roadTexture.getSize().y);
        }

        scoreText.setString("Score: " + std::to_string(score));

        window.clear();
        window.draw(roadSprite1);
        window.draw(roadSprite2);
        window.draw(player.getSprite());

        for (const auto& barrel : greenBarrels) {
            window.draw(barrel.getSprite());
        }
        for (const auto& barrel : blueBarrels) {
            window.draw(barrel.getSprite());
        }
        for (const auto& car : redCars) {
            window.draw(car.getSprite());
        }

        window.draw(scoreText);
        window.display();
    }

    return 0;
}
