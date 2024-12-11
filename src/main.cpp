#include "carro.hpp"
#include "carretera.hpp"
#include "juego.hpp"
#include "obstaculo.hpp"
#include <SFML/Graphics.hpp>
#include<vector>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

Carretera::Carretera(sf::Texture& textura, sf::RenderWindow& window) : window(window), detenida(false) {
    sprite.setTexture(textura);
    sprite2.setTexture(textura);
    sprite2.setPosition(0, -sprite.getTexture()->getSize().y);
}

void Carretera::mover(float velocidad, const Carro& carro) {
    if (carro.getSprite().getPosition().x <= 100 or carro.getSprite().getPosition().x >= 700) {
        detener();
    }

    if (!detenida) {
        sprite.move(0, velocidad);
        sprite2.move(0, velocidad);

        if (sprite.getPosition().y >= window.getSize().y) {
            sprite.setPosition(0, sprite2.getPosition().y - sprite.getTexture()->getSize().y);
        }
        if (sprite2.getPosition().y >= window.getSize().y) {
            sprite2.setPosition(0, sprite.getPosition().y - sprite2.getTexture()->getSize().y);
        }
    }
}

void Carretera::dibujar() {
    window.draw(sprite);
    window.draw(sprite2);
}

bool Carretera::estaDetenida() const {
    return detenida;
}

void Carretera::detener() {
    detenida = true;
}

void Carretera::reanudar() {
    detenida = false;
}


Carro::Carro(sf::Texture& textura, float posicionInicialX, float posicionInicialY) {
    sprite.setTexture(textura);
    sprite.setPosition(posicionInicialX, posicionInicialY);

    rangoMinX = 100.0f;
    rangoMaxX = 700.0f;
    posicionYConstante = posicionInicialY;

    sf::Texture texturaMensaje;
    if (!texturaMensaje.loadFromFile("./assets/images/game over.png")) {
        std::cerr << "Error al cargar la textura del mensaje de pérdida" << std::endl;
    }
    mensajePerdida.setTexture(texturaMensaje);
    mensajePerdida.setPosition(300, 250);
}

void Carro::mover(float velocidad, sf::Keyboard::Key A, sf::Keyboard::Key D) {
    if (sf::Keyboard::isKeyPressed(A)) {
        sprite.move(-velocidad, 0);
    }
    if (sf::Keyboard::isKeyPressed(D)) {
        sprite.move(velocidad, 0);
    }
}

bool Carro::verificarSalidaRango() const {
    return (sprite.getPosition().x < rangoMinX || sprite.getPosition().x > rangoMaxX);
}

void Carro::dibujar(sf::RenderWindow& window) {
    if (verificarSalidaRango()) {
        window.draw(mensajePerdida);
        
    } else {
        window.draw(sprite);
    }
}

sf::Sprite Carro::getSprite() const {
    return sprite;
}

sf::FloatRect Carro::getBounds() const {
    return sprite.getGlobalBounds();
}


#include "juego.hpp"

Juego::Juego(sf::RenderWindow& ventana) : ventana(ventana), tiempoJuego(0), score(0), juegoActivo(false) {
    if (!fuente.loadFromFile("./assets/fonts/Minecraft.ttf")) {
        std::cerr << "Error al cargar la fuente" << std::endl;
    }

    textoScore.setFont(fuente);
    textoScore.setCharacterSize(50);
    textoScore.setFillColor(sf::Color::Black);
    textoScore.setPosition(40, 50);

    textoCuentaRegresiva.setFont(fuente);
    textoCuentaRegresiva.setCharacterSize(100);
    textoCuentaRegresiva.setFillColor(sf::Color::Red);
    textoCuentaRegresiva.setPosition(250, 200);

 // Posición de la imagen de "3, 2, 1, Go"
}

void Juego::inicializar() {
    juegoActivo = true;
    tiempoJuego = 0;
    score = 0;

    // Mostrar la cuenta regresiva inicial
    for (int i = 3; i > 0; i--) {
        textoCuentaRegresiva.setString(std::to_string(i));
        ventana.clear();
        ventana.draw(textoCuentaRegresiva);
        ventana.display();
        sf::sleep(sf::seconds(1));
    }

    textoCuentaRegresiva.setString("Go!");
    ventana.clear();
    ventana.draw(textoCuentaRegresiva);
    ventana.display();
    sf::sleep(sf::seconds(1));
}

void Juego::actualizar(float deltaTime, Carro& carro, std::vector<sf::Sprite>& carrosAzules, std::vector<sf::Sprite>& bidones) {
    if (juegoActivo) {
        tiempoJuego += deltaTime;

        // Actualizar el puntaje según el tiempo
        score = static_cast<int>(tiempoJuego);

        // Llamar a la función de colisiones
        manejarColisiones(carro, carrosAzules, bidones);

        // Mostrar el puntaje
        textoScore.setString("Score: " + std::to_string(score));
    }
}

void Juego::dibujar() {
    if (juegoActivo) {
        ventana.draw(textoScore);
    }
}

void Juego::manejarColisiones(Carro& carro, std::vector<sf::Sprite>& carrosAzules, std::vector<sf::Sprite>& bidones) {
    if (juegoActivo) {
        for (auto& carroAzul : carrosAzules) {
            if (carro.getBounds().intersects(carroAzul.getGlobalBounds())) {
                score -= 50;
                // Reubicar el carro azul fuera de la vista, simular la eliminación de la colisión.
                carroAzul.setPosition(-100, -100);
            }
        }

        for (auto& bidon : bidones) {
            if (carro.getBounds().intersects(bidon.getGlobalBounds())) {
                score += 100;
                // Reubicar el bidón fuera de la vista, simular que ha sido recolectado.
                bidon.setPosition(-100, -100);
            }
        }

        // Verificar si el carro está fuera del rango permitido (esto ya se maneja en la clase Carro).
        if (carro.verificarSalidaRango()) {
            juegoActivo = false;
        }
    }
}

int Juego::getScore() const {
    return score;
}

bool Juego::esJuegoActivo() const {
    return juegoActivo;
}


int main() {
    srand(static_cast<unsigned int>(time(0)));
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Turbo Racing");

    sf::Texture texturaCarro;
    if (!texturaCarro.loadFromFile("./assets/images/pixel_racecar_orange.png")) {
        std::cerr << "Error al cargar la textura del carro" << std::endl;
        return 1;
    }
    sf::Texture texturaCarretera;
    if (!texturaCarretera.loadFromFile("./assets/images/carretera.png")) {
        std::cerr << "Error al cargar la textura de la carretera" << std::endl;
        return 1;
    }
    sf::Texture texturaObstaculo;
    if (!texturaObstaculo.loadFromFile("./assets/images/pixel_racecar_blue.png")) {
    std::cerr << "Error al cargar la textura del obstáculo" << std::endl;
}
    std::vector<sf::Sprite> carrosAzules;  // Vector para los carros azules
    std::vector<sf::Sprite> bidones;       // Vector para los bidones

    // Instancia de la carretera y el carro
    Carretera carretera(texturaCarretera, window);
    Carro carro(texturaCarro, 400, 500);

    Obstaculo obstaculo;
    obstaculo.inicializar(100, 700);


    // Instancia del juego
    Juego juego(window);

    // Inicializar el juego
    juego.inicializar();

    float acel=0.01f;
    float velocidad = 0.20f;

    velocidad+=acel;

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (carro.verificarSalidaRango() && event.mouseButton.button == sf::Mouse::Left) {
                    // Reiniciar el juego y la carretera
                    carro = Carro(texturaCarro, 400, 500);  // Crear una nueva instancia de Carro
                    carretera.reanudar();  // Llamar al método de la instancia de Carretera
                    juego.inicializar();  // Llamar al método de la instancia de Juego
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();

        // Mover la carretera y el carro
        carretera.mover(200 * deltaTime, carro);
        carro.mover(velocidad, sf::Keyboard::Left, sf::Keyboard::Right);
        juego.actualizar(deltaTime, carro, carrosAzules, bidones);
        obstaculo.actualizar(deltaTime);

        window.clear();
        carretera.dibujar();
        carro.dibujar(window);
        juego.dibujar();
        obstaculo.dibujar(window);
        window.display();
    }

    return 0;
}




Obstaculo::Obstaculo() : tiempoUltimaGeneracion(0), tiempoEntreGeneraciones(1), tiempoAcumulado(0), cantidadMaxima(5) {
    // Cargar la textura de los obstáculos
    if (!texturaObstaculo.loadFromFile("./assets/images/pixel_racecar_blue.png")) {
        std::cerr << "Error al cargar la textura del obstáculo" << std::endl;
    }
}

// Inicializar con valores de rango de posición
void Obstaculo::inicializar(float xMin, float xMax) {
    this->xMin = xMin;
    this->xMax = xMax;
}

void Obstaculo::actualizar(float deltaTime) {
    tiempoAcumulado += deltaTime;

    if (tiempoAcumulado > tiempoUltimaGeneracion) {
        if (obstaculos.size() < cantidadMaxima) {
            generarObstaculo();
            tiempoUltimaGeneracion = tiempoAcumulado + tiempoEntreGeneraciones;
        }

        cantidadMaxima = std::min(15, cantidadMaxima + 1);
        tiempoEntreGeneraciones = std::max(0.5f, tiempoEntreGeneraciones - 0.1f);
    }

    for (auto& obstaculo : obstaculos) {
        obstaculo.move(0, 2);
    }

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
    float xPos = xMin + rand() % (static_cast<int>(xMax - xMin + 1));
    float yPos = -50.0f;

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