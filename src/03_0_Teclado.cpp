#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 700), "./assets/images/carretera.png");

    // Cargar texturas y crear sprites (código simplificado)
    sf::Texture texturaCarretera;
    texturaCarretera.loadFromFile("./assets/images/carretera.png");
    sf::Sprite spriteCarretera(texturaCarretera);
    // ... lo mismo para las otras texturas y sprites

    // Variables de desplazamiento
    float velocidadDesplazamiento = 1.0f;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Mover los sprites
        spriteCarretera.move(0, velocidadDesplazamiento);
        // ... mover los otros sprites

        // Lógica de bucle para la carretera
        if (spriteCarretera.getPosition().y > window.getSize().y) {
            spriteCarretera.setPosition(0, -spriteCarretera.getTextureRect().height);
        }

        // Dibujar los sprites
       // window.clear();
        window.draw(spriteCarretera);
        // ... dibujar los otros sprites
        window.display();
    }

    return 0;
}