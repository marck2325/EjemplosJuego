#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <iostream>
#include <ctime> // Para time()

class Obstaculo {
public:
    Obstaculo();
    void inicializar(float xMin, float xMax);
    void actualizar(float deltaTime);
    void dibujar(sf::RenderWindow& ventana);
    std::vector<sf::Sprite>& obtenerObstaculos();
    void reiniciar();

private:
    void generarObstaculo();
    
    sf::Texture texturaObstaculo;
    std::vector<sf::Sprite> obstaculos;
    float tiempoUltimaGeneracion;
    float tiempoEntreGeneraciones;
    float tiempoAcumulado;
    int cantidadMaxima;
    float xMin, xMax;
};