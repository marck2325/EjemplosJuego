#ifndef CARRETERA_HPP
#define CARRETERA_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Carretera {
private:
    float playerX;
    float roadSpeed;
    int score;
    bool gameOver; // Nuevo miembro agregado
    sf::Text scoreText;

public:
    Carretera();
    void startGame(sf::RenderWindow& window, sf::Font& font);
    void movePlayerLeft(float distance);
    void movePlayerRight(float distance);
    void update(const sf::Vector2u& windowSize, float deltaTime);
    float getPlayerX() const;
    const sf::Text& getScoreText() const;
    void increaseScore();
    bool isGameOver() const; // Método para verificar si el juego terminó
    void mover(float velocidad, bool juegoActivo); // Control de velocidad
    void setPosition(int xPos);
};

#endif // CARRETERA_HPP