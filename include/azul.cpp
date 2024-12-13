#include "Azul.hpp"

Azul::Azul() : x(0), y(0) {}

int Azul::getX() const {
    return x;
}

int Azul::getY() const {
    return y;
}

void Azul::setPosition(int xPos, int yPos) {
    x = xPos;
    y = yPos;
}
