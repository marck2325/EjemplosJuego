#include "juego.hpp"

Juego::Juego(sf::RenderWindow& ventana) : ventana(ventana), tiempoJuego(0), score(0), juegoActivo(false) {
    if (!fuente.loadFromFile("./assets/fonts/Minecraft.ttf")) {
        std::cerr << "Error al cargar la fuente" << std::endl;
    }

    textoScore.setFont(fuente);
    textoScore.setCharacterSize(30);
    textoScore.setFillColor(sf::Color::White);
    textoScore.setPosition(10, 10);

    textoCuentaRegresiva.setFont(fuente);
    textoCuentaRegresiva.setCharacterSize(100);
    textoCuentaRegresiva.setFillColor(sf::Color::Red);
    textoCuentaRegresiva.setPosition(250, 200);

    if (!texturaCuentaRegresiva.loadFromFile("./assets/images/3.png")) {
        std::cerr << "Error al cargar la textura de cuenta regresiva" << std::endl;
    }
    spriteCuentaRegresiva.setTexture(texturaCuentaRegresiva);
    spriteCuentaRegresiva.setPosition(200, 150); // Posición de la imagen de "3, 2, 1, Go"
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
