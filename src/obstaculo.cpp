#include "obstaculo.hpp"

Obstaculo::Obstaculo() : tiempoUltimaGeneracion(0), tiempoEntreGeneraciones(1), tiempoAcumulado(0), cantidadMaxima(5) {
    srand(static_cast<unsigned int>(time(0))); // Inicializar la semilla de la función rand()

    // Cargar la textura de los obstáculos
    if (!texturaObstaculo.loadFromFile("./assets/images/pixel_racecar_blue.png")) {
        std::cerr << "Error al cargar la textura del obstáculo" << std::endl;
    }
}

void Obstaculo::inicializar(sf::Texture& textura, float xMin, float xMax) {
    texturaObstaculo = textura;
    this->xMin = xMin;
    this->xMax = xMax;
}

void Obstaculo::actualizar(float deltaTime) {
    tiempoAcumulado += deltaTime;

    // Incrementar la frecuencia de generación de obstáculos con el tiempo
    if (tiempoAcumulado > tiempoUltimaGeneracion) {
        if (obstaculos.size() < cantidadMaxima) {
            generarObstaculo();
            tiempoUltimaGeneracion = tiempoAcumulado + tiempoEntreGeneraciones;
        }

        // Ajustar la cantidad máxima de obstáculos y el tiempo entre generaciones
        cantidadMaxima = std::min(15, cantidadMaxima + 1); // Aumentar la cantidad máxima de obstáculos
        tiempoEntreGeneraciones = std::max(0.5f, tiempoEntreGeneraciones - 0.1f); // Disminuir el tiempo entre generaciones
    }

    // Mover obstáculos hacia abajo
    for (auto& obstaculo : obstaculos) {
        obstaculo.move(0, 2); // Velocidad de movimiento en Y
    }

    // Eliminar obstáculos que estén fuera de la pantalla
    obstaculos.erase(std::remove_if(obstaculos.begin(), obstaculos.end(), 
                [this](const sf::Sprite& s) { return s.getPosition().y > 600; }), 
                obstaculos.end());
}

void Obstaculo::dibujar(sf::RenderWindow& ventana) {
    for (const auto& obstaculo : obstaculos) {
        ventana.draw(obstaculo);
    }
}

std::vector<sf::Sprite>& Obstaculo::obtenerObstaculos() {
    return obstaculos;
}

void Obstaculo::generarObstaculo() {
    float xPos = static_cast<float>(rand() % static_cast<int>(xMax - xMin + 1) + xMin);
    float yPos = -50.0f; // Posición inicial fuera de la pantalla

    sf::Sprite nuevoObstaculo(texturaObstaculo);
    nuevoObstaculo.setPosition(xPos, yPos);

    obstaculos.push_back(nuevoObstaculo);
}

void Obstaculo::reiniciar() {
    obstaculos.clear();
    tiempoUltimaGeneracion = 0;
    tiempoEntreGeneraciones = 1;
    tiempoAcumulado = 0;
    cantidadMaxima = 5;
}
