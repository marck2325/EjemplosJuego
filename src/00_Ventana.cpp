#include <SFML/Graphics.hpp>
#include<iostream>
int main()
{
    // Crear una ventana
    sf::RenderWindow window(sf::VideoMode(800, 600), "./assets/images/pixel_racecar_orange.png");

    // Cargar la textura del carro
    sf::Texture texture;
    if (!texture.loadFromFile("./assets/images/pixel_racecar_orange.png")) // Asegúrate de tener el archivo "carro.png" en la misma carpeta que tu código
    {
        std::cerr << "Error al cargar la textura del carro" << std::endl;
        return 1;
    }

    // Crear un sprite a partir de la textura
    sf::Sprite sprite(texture);

    // Posicionar el sprite inicialmente
    sprite.setPosition(800, 150);

    // Velocidad de movimiento
    float velocidad = .50f;

    // Bucle principal del juego
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Controlar el movimiento con las teclas A y D
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            sprite.move(-velocidad, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            sprite.move(velocidad, 0);
        }

        // Limpiar la ventana
        window.clear();

        // Dibujar el sprite
        window.draw(sprite);

        // Mostrar la ventana
        window.display();
    }

    return 0;
}