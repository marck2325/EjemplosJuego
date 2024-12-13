#ifndef AZUL_HPP
#define AZUL_HPP

class Azul {
public:
    Azul();
    int getX() const;
    int getY() const;
    void setPosition(int xPos, int yPos);

private:
    int x, y;
};

#endif
