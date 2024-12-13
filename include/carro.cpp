// carro.cpp
#include "carro.hpp"

Carro::Carro() : x(400), score(0) {}

void Carro::moveLeft(float delta) {
    x -= delta;
    if (x < 150) x = 150; // Limitar a los bordes
}

void Carro::moveRight(float delta) {
    x += delta;
    if (x > 700) x = 700; // Limitar a los bordes
}
int Carro::getX() const {
    return static_cast<int>(x);
}

void Carro::resetScore() {
    score = 0;
}

void Carro::adjustScore(int delta) {
    score += delta;
}

int Carro::getScore() const {
    return score;
}

void Carro::setPosition(int xPos) {
    x = xPos;
}