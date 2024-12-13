#ifndef BIDON_HPP
#define BIDON_HPP

class Bidon {
private:
    int x; // Posición en X
    int y; // Posición en Y

public:
    Bidon();
    int getX() const; // Obtener posición X
    int getY() const; // Obtener posición Y
    void setPosition(int x, int y);
    void updatePosition(float deltaTime);
};

#endif // BIDON_HPP
