// carro.hpp
#ifndef CARRO_HPP
#define CARRO_HPP

class Carro {
public:
    Carro();
    void moveLeft(float delta);   // Ahora acepta un desplazamiento
    void moveRight(float delta); // Ahora acepta un desplazamiento
    int getX() const;
    void resetScore();
    void adjustScore(int delta);
    int getScore() const;
    void setPosition(int xPos);

private:
    float x;  // Cambiado a float para permitir movimientos más suaves
    int score;
};

#endif
