#ifndef JUEGO_HPP
#define JUEGO_HPP

#include <SFML/Graphics.hpp>
#include "carro.hpp"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include "Azul.hpp"

class Juego
{
public:
    Juego(sf::RenderWindow &ventana); // Constructor que inicializa la ventana
    void ejecutar();
    void inicializar();
    void actualizar();
    void dibujar();
    int getScore() const;
    bool esJuegoActivo() const;

private:
    sf::RenderWindow &ventana; // Referencia a la ventana de renderizado
    sf::Font fuente;
    sf::Text textoScore;
    sf::Text textoCuentaRegresiva;
    sf::Texture texturaCuentaRegresiva;
    sf::Sprite spriteCuentaRegresiva;
    float tiempoJuego;
    int score;
    bool juegoActivo;
    int cantidadMaxima;
    std::vector<Azul> carros;
    int intervaloGeneracion;
    std::chrono::steady_clock::time_point lastGenerationTime;

    void generarCarro();
    void moverCarros();
    void controlarGeneracion();
    void dibujarCarros();
    int generarPosicionAleatoriaX();
};

#endif // JUEGO_HPP
