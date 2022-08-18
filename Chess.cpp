#include "Chess.h"
#include "Board.h"
#include "stdio.h"
#include "StringUtil.h"

Chess::Chess()
{
}

Chess::Chess(int col, int row, char name)
{
    this->row = row;
    this->col = col;
    this->name = name;
    this->isRed = StringUtil::isUpper(name);
    this->dead = false;
}

void Chess::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    CircleShape circle(CHESS_SIZE / 2);
    circle.setPosition(Vector2f(this->col * GRID_SIZE + 5, this->row * GRID_SIZE + PADDING));
    circle.setFillColor(this->dead ? Color(85, 85, 85) : this->isRed ? Color::White : Color::Black);
    circle.setOutlineThickness(LINE_WIDTH);
    circle.setOutlineColor(this->isRed ? Color::Black : Color::White);
    Text text;
    Font font;
    font.loadFromFile(FONT_PATH);
    text.setFont(font); // font is a sf::Font
    text.setString(StringUtil::translate(this->name).c_str());
    text.setCharacterSize(45); // in pixels, not points!
    text.setFillColor(this->dead ? Color(176, 176, 176):this->isRed ? Color::Black : Color::White);
    text.setPosition(Vector2f(this->col * GRID_SIZE + 7, this->row * GRID_SIZE + COORDINATE_HEIGHT));

    target.draw(circle, states);
    target.draw(text, states);
}
