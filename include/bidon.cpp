#include "bidon.hpp"
#include <cstdlib>

Bidon::Bidon() : x(500) {}

int Bidon::getX() const {
    return x;
}

void Bidon::setPosition(int xPos,int yPos) {
    x = xPos;
}
int Bidon::getY() const { // Implementación de getY()
    return y;
}

void Bidon::updatePosition(float deltaTime) {
    y += 100 * deltaTime; // Ejemplo de movimiento hacia abajo
    if (y > 600) {  // Si sale de la pantalla, regenera posición
        y = -50;
        x = 100 + rand() % 600;  // Genera una posición X aleatoria
    }
}