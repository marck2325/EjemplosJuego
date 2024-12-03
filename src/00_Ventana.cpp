#include <SFML/Graphics.hpp>

int main() {
    // Crear una ventana de 800x600 píxeles
    sf::RenderWindow window(sf::VideoMode(800, 600), "Fondo del juego");

    // Cargar la imagen de fondo
    sf::Texture texture;
    if (!texture.loadFromFile("./assets/images/carretera.png")) {
        return -1;  // Si no se carga la imagen, salir
    }

    // Crear un sprite para mostrar la imagen de fondo
    sf::Sprite sprite(texture);

    // Bucle principal del juego
    while (window.isOpen()) {
        // Manejo de eventos
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();  // Si se cierra la ventana, salir
        }

        // Limpiar la ventana con un color (en este caso negro)
        window.clear(sf::Color::Black);

        // Dibujar la imagen de fondo
        window.draw(sprite);

        // Mostrar todo lo que hemos dibujado
        window.display();
    }

    return 0;
}