#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

#define CHESS_SIZE 50

class Chess: public Drawable
{
public:
    int row;
    int col;
    bool isRed;
    char name;
    bool dead;

    bool operator==(const Chess& p)
    {
        if (this->row == p.row && this->col == p.col && this->name == p.name)
        {
            return true;
        }
        return false;
    }
    Chess();
    Chess(int col, int row, char name);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

