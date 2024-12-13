#include "carretera.hpp"
#include <thread>
#include <chrono>
#include <algorithm>
#include <cstdlib> // Para rand()
#include <ctime> 

Carretera::Carretera() : playerX(400), roadSpeed(200.0f), score(0) {}

void Carretera::startGame(sf::RenderWindow& window, sf::Font& font) {
    gameOver = false; // Reinicia el estado del juego
    score = 0;        // Reinicia el puntaje
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(10, 10);
    scoreText.setString("Score: 0");

        sf::Text countdownText;
    countdownText.setFont(font);
    countdownText.setCharacterSize(50);
    countdownText.setFillColor(sf::Color::Red);
    countdownText.setPosition(window.getSize().x / 2 - 50, window.getSize().y / 2 - 50);

    // Mensajes del contador
    std::string countdownMessages[] = {"1...", "2...", "3...", "Ready, Go!"};

    for (const auto &message : countdownMessages) {
        countdownText.setString(message);
        window.clear();
        window.draw(countdownText);
        window.display();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
void Carretera::movePlayerLeft(float distance) {
    playerX -= distance;
    if (playerX < 0) playerX = 0;
}

void Carretera::movePlayerRight(float distance) {
    playerX += distance;
    if (playerX > 800) playerX = 800;
}

void Carretera::update(const sf::Vector2u& windowSize, float deltaTime) {
    // Actualizar puntuación o lógica adicional si es necesario
    score += static_cast<int>(deltaTime * 100);
    scoreText.setString("Score: " + std::to_string(score));
}

float Carretera::getPlayerX() const {
    return playerX;
}

const sf::Text& Carretera::getScoreText() const {
    return scoreText;
}

void Carretera::increaseScore() {
    score += 10;
}

void Carretera::mover(float velocidad, bool juegoActivo) {
    if (juegoActivo) {
        roadSpeed = velocidad;
    } else {
        roadSpeed = 0;
    }
}

bool Carretera::isGameOver() const {
    return gameOver;
}