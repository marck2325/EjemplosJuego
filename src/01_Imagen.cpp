#include <SFML/Graphics.hpp>

int main() {
    // Crear una ventana de 800x600 píxeles
    sf::RenderWindow window(sf::VideoMode(800, 600), "Juego de Carro");

    // Cargar la imagen de los frames del carro
    sf::Texture carTexture;
    if (!carTexture.loadFromFile("./assets/images/pikachu.png")) {
        return -1;  // Si no se carga la imagen, salir
    }

    // Crear un sprite para el carro
    sf::Sprite carSprite(carTexture);
    
    // Establecer las dimensiones de cada frame (esto dependerá del tamaño de tu hoja de sprites)
    const int frameWidth = 100;  // Ancho de cada frame
    const int frameHeight = 100; // Alto de cada frame
    int currentFrame = 0;        // Contador de los frames

    // Bucle principal del juego
    while (window.isOpen()) {
        // Manejo de eventos
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();  // Si se cierra la ventana, salir
        }

        // Animar el carro (cambiar el frame)
        if (currentFrame < 3) { // Suponiendo que tienes 3 frames en tu hoja de sprites
            currentFrame++;
        } else {
            currentFrame = 0;
        }

        // Cambiar el rectángulo de textura para mostrar el frame adecuado
        carSprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));

        // Limpiar la ventana con un color (en este caso negro)
        window.clear(sf::Color::Black);

        // Dibujar el carro
        window.draw(carSprite);

        // Mostrar todo lo que hemos dibujado
        window.display();
    }

    return 0;
}