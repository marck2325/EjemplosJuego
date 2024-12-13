#include "carretera.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <cstdlib> // Para rand()
#include <ctime>  
#include "juego.hpp"
/*
void Carretera::mover(float velocidad, bool juegoActivo) {
    if (juegoActivo) {
        playerX.setPosition(playerX.getX() + velocidad);
    }
}*/
Juego::Juego(sf::RenderWindow& ventana)
    : ventana(ventana), score(0), juegoActivo(false), cantidadMaxima(10), intervaloGeneracion(3000) {
    lastGenerationTime = std::chrono::steady_clock::now();
    srand(static_cast<unsigned>(time(0))); // Inicializar semilla aleatoria
}

void Juego::generarCarro() {
    Azul nuevoCarro;
    int x = generarPosicionAleatoriaX();
    int y = -30; // Iniciar fuera de la pantalla (parte superior)
    nuevoCarro.setPosition(x, y);
    carros.push_back(nuevoCarro);
}

void Juego::moverCarros() {
    for (auto& carro : carros) {
        int y = carro.getY() + 2; // Mover el carro hacia abajo
        carro.setPosition(carro.getX(), y);
    }

    // Eliminar carros que salen de la pantalla
    carros.erase(std::remove_if(carros.begin(), carros.end(), [](Azul& carro) {
        return carro.getY() > 600;  // Suponiendo que la altura de la pantalla es 600
    }), carros.end());
}

void Juego::controlarGeneracion() {
    auto now = std::chrono::steady_clock::now();
    int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastGenerationTime).count();

    if (elapsed >= intervaloGeneracion) {
        generarCarro();
        lastGenerationTime = now;
        
        // Reducir el intervalo progresivamente
        if (intervaloGeneracion > 1000) {
            intervaloGeneracion -= 100; // Aumentar la frecuencia de generación
        }
    }
}

void Juego::dibujarCarros() {
    for (const auto& carro : carros) {
        std::cout << "Carro en posición (" << carro.getX() << ", " << carro.getY() << ")\n";
    }
}

int Juego::generarPosicionAleatoriaX() {
    return rand() % (700 - 100 + 1) + 100; // Rango de 100 a 700
}

void Juego::ejecutar() {
    while (true) {
        controlarGeneracion(); // Controlar la generación de carros
        moverCarros();         // Mover carros
        dibujarCarros();       // Mostrar posiciones en consola (puedes adaptarlo a una interfaz gráfica)
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Controlar la velocidad del loop
    }
}