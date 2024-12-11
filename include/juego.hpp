#ifndef JUEGO_HPP
#define JUEGO_HPP

#include <SFML/Graphics.hpp>
#include "carro.hpp"
#include <vector>

class Juego {
public:
    Juego(sf::RenderWindow& ventana);
    void inicializar();
    void actualizar(float deltaTime, Carro& carro, std::vector<sf::Sprite>& carrosAzules, std::vector<sf::Sprite>& bidones);
    void dibujar();
    int getScore() const;
    bool esJuegoActivo() const;

private:
    sf::RenderWindow& ventana;
    sf::Font fuente;
    sf::Text textoScore;
    sf::Text textoCuentaRegresiva;
    sf::Texture texturaCuentaRegresiva;
    sf::Sprite spriteCuentaRegresiva;
    float tiempoJuego;
    int score;
    bool juegoActivo;

    void manejarColisiones(Carro& carro, std::vector<sf::Sprite>& carrosAzules, std::vector<sf::Sprite>& bidones);
};

#endif // JUEGO_HPP
