#include "Board.h"
#include "StringUtil.h"

void Board::draw(RenderTarget& target, RenderStates states) const
{
    states.transform *= getTransform();
    RectangleShape rectangle(Vector2f(MARGIN + 8 * GRID_SIZE, MARGIN + 9 * GRID_SIZE));
    rectangle.setPosition(MARGIN, MARGIN + COORDINATE_HEIGHT);
    rectangle.setFillColor(Color::White);
    rectangle.setOutlineThickness(LINE_WIDTH * 2);
    rectangle.setOutlineColor(Color::Black);
    target.draw(rectangle, states);
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 9; j++)
        {
            if (j != 4)
            {
                RectangleShape rect(Vector2f(GRID_SIZE, GRID_SIZE));
                rect.setPosition(PADDING + i * GRID_SIZE, PADDING + j * GRID_SIZE + COORDINATE_HEIGHT);
                rect.setFillColor(Color::White);
                rect.setOutlineThickness(LINE_WIDTH);
                rect.setOutlineColor(Color::Black);
                target.draw(rect, states);
            }
        }
    }
    this->drawCoordinate(target, states);
    this->drawDiagonal(target, states);
    this->drawDecorate(target, states);
    this->drawTracks(target, states);
    this->drawChesses(target, states);
    this->drawStep(target, states);
    this->drawStaveBox(target, states);
    this->drawStave(target, states);
    this->drawButton(target, states);
}

void Board::drawDiagonal(RenderTarget& target, RenderStates states) const
{
    drawLine(target, states, PADDING + 3 * GRID_SIZE, PADDING + COORDINATE_HEIGHT, PADDING + 5 * GRID_SIZE, PADDING + 2 * GRID_SIZE + COORDINATE_HEIGHT);
    drawLine(target, states, PADDING + 5 * GRID_SIZE, PADDING + COORDINATE_HEIGHT, PADDING + 3 * GRID_SIZE, PADDING + 2 * GRID_SIZE + COORDINATE_HEIGHT);
    drawLine(target, states, PADDING + 3 * GRID_SIZE, PADDING + 7 * GRID_SIZE + COORDINATE_HEIGHT, PADDING + 5 * GRID_SIZE, PADDING + 9 * GRID_SIZE +
             COORDINATE_HEIGHT);
    drawLine(target, states, PADDING + 5 * GRID_SIZE, PADDING + 7 * GRID_SIZE + COORDINATE_HEIGHT, PADDING + 3 * GRID_SIZE, PADDING + 9 * GRID_SIZE +
             COORDINATE_HEIGHT);
}

void Board::drawLine(RenderTarget& target, RenderStates states, int x, int y, int x1, int y1) const
{
    LineShape line(Vector2f(x - 1, y), Vector2f(x1 - 1, y1));
    target.draw(line, states);
}

void Board::drawCoordinate(RenderTarget& target, RenderStates states) const
{
    Font font;
    font.loadFromFile(FONT_PATH);
    Text text;
    text.setFont(font); // font is a sf::Font
    text.setCharacterSize(50); // in pixels, not points!
    text.setFillColor(Color::Black);
    text.setString(L"楚 河");
    text.setPosition(Vector2f(1 * GRID_SIZE, 5 * GRID_SIZE - 10));
    target.draw(text, states);
    text.setString(L"漢 界");
    text.setPosition(Vector2f(6 * GRID_SIZE, 5 * GRID_SIZE - 10));
    target.draw(text, states);

    text.setCharacterSize(20);
    font.loadFromFile(FONT_SONG_PATH);
    text.setFont(font);
    for (int i = 0; i < 9; i++)
    {
        wstring valstr;
        valstr.append(1, i + 1 + '0');
        text.setString(valstr.c_str());
        text.setPosition(Vector2f(i * GRID_SIZE + MARGIN, 0));
        target.draw(text, states);
        text.setString(COORDINATE[i]);
        text.setPosition(Vector2f(i * GRID_SIZE + MARGIN, 9 * GRID_SIZE + 3 * PADDING));
        target.draw(text, states);
    }
}

void Board::drawDecorate(RenderTarget& target, RenderStates states) const
{
    int decorate[14][2] = { {1, 2}, { 7, 2 }, { 0, 3 }, { 2, 3 }, { 4, 3 }, { 6, 3 }, { 8, 3 }, { 1, 7 }, { 7, 7 }, { 0, 6 }, { 2, 6 }, { 4, 6 }, { 6, 6 }, { 8, 6 } };

    for (size_t i = 0; i < 14; i++)
    {
        int margin = 5;
        int x = decorate[i][0];
        int y = decorate[i][1];
        if (x != 0)
        {
            //竖
            drawLine(target, states, x * GRID_SIZE - margin + PADDING, y * GRID_SIZE - 3 * margin + PADDING +
                     COORDINATE_HEIGHT,
                     x * GRID_SIZE - margin + PADDING, y * GRID_SIZE - margin + PADDING + COORDINATE_HEIGHT);
            //横
            drawLine(target, states, x * GRID_SIZE - margin + PADDING, y * GRID_SIZE - margin + PADDING +
                     COORDINATE_HEIGHT, x * GRID_SIZE - 3 * margin + PADDING, y * GRID_SIZE - margin + PADDING + COORDINATE_HEIGHT);
        }
        if (x != 0)
        {
            drawLine(target, states, x * GRID_SIZE + PADDING - margin, y * GRID_SIZE + PADDING + 3 * margin +
                     COORDINATE_HEIGHT,
                     x * GRID_SIZE + PADDING - margin, y * GRID_SIZE + PADDING + margin + COORDINATE_HEIGHT);
            drawLine(target, states, x * GRID_SIZE + PADDING - margin, y * GRID_SIZE + PADDING + margin +
                     COORDINATE_HEIGHT, x * GRID_SIZE + PADDING - 3 * margin, y * GRID_SIZE + PADDING + margin + COORDINATE_HEIGHT);
        }
        if (x != 8)
        {
            drawLine(target, states, x * GRID_SIZE + margin + PADDING, y * GRID_SIZE + PADDING - 3 * margin +
                     COORDINATE_HEIGHT,
                     x * GRID_SIZE + margin + PADDING, y * GRID_SIZE - margin + PADDING + COORDINATE_HEIGHT);
            drawLine(target, states, x * GRID_SIZE + margin + PADDING, y * GRID_SIZE + PADDING - margin +
                     COORDINATE_HEIGHT, x * GRID_SIZE + 3 * margin + PADDING, y * GRID_SIZE - margin + PADDING + COORDINATE_HEIGHT);
        }
        if (x != 8)
        {
            drawLine(target, states, x * GRID_SIZE + margin + PADDING, y * GRID_SIZE + PADDING - 3 * margin +
                     COORDINATE_HEIGHT +
                     PADDING, x * GRID_SIZE + margin + PADDING, y * GRID_SIZE + margin + PADDING +
                     COORDINATE_HEIGHT);
            drawLine(target, states, x * GRID_SIZE + margin + PADDING, y * GRID_SIZE + margin + PADDING +
                     COORDINATE_HEIGHT, x * GRID_SIZE + 3 * margin + PADDING, y * GRID_SIZE + margin + PADDING + COORDINATE_HEIGHT);
        }
    }

    drawLine(target, states, PADDING, 4 * GRID_SIZE + COORDINATE_HEIGHT + PADDING, PADDING, 5 * GRID_SIZE + COORDINATE_HEIGHT + PADDING);
    drawLine(target, states, PADDING + 8 * GRID_SIZE + 2, 4 * GRID_SIZE + COORDINATE_HEIGHT + PADDING, PADDING + 8 * GRID_SIZE + 2, 5 * GRID_SIZE + COORDINATE_HEIGHT +
             PADDING);
}

void Board::drawTracks(RenderTarget& target, RenderStates states) const
{
    if(StringUtil::valid(tracks.first))
    {
        int row = tracks.first.row;
        int col = tracks.first.col;
        track(target, states, row, col);
    }
    if(StringUtil::valid(tracks.second))
    {
        int row = tracks.second.row;
        int col = tracks.second.col;
        track(target, states, row, col);
    }
}

void Board::track(RenderTarget& target, RenderStates states, int row, int col) const
{
    int x = col * GRID_SIZE;
    int y = row * GRID_SIZE + COORDINATE_HEIGHT;
    drawLine(target, states, x, y + 10, x, y);
    drawLine(target, states, x, y, x + 10, y);

    x += GRID_SIZE;
    drawLine(target, states, x - 10, y, x, y);
    drawLine(target, states, x, y, x, y + 10);

    y += GRID_SIZE;
    drawLine(target, states, x, y - 10, x, y);
    drawLine(target, states, x, y, x - 10, y);

    x -= GRID_SIZE;
    drawLine(target, states, x, y - 10, x, y);
    drawLine(target, states, x, y, x + 10, y);
}

void Board::drawChesses(RenderTarget& target, RenderStates states) const
{
    for(Chess chess : this->map)
    {
        target.draw(chess, states);
    }
}

void Board::drawStep(RenderTarget& target, RenderStates states) const
{
    for (Point p : passibleMove)
    {
        CircleShape circle(CHESS_SIZE / 4);
        circle.setPosition(p.col * GRID_SIZE + PADDING, p.row * GRID_SIZE + PADDING + COORDINATE_HEIGHT);
        circle.setOutlineThickness(LINE_WIDTH);
        circle.setOutlineColor(Color::Black);
        circle.setOrigin(Vector2f(CHESS_SIZE / 4, CHESS_SIZE / 4));
        target.draw(circle, states);
    }
}

void Board::drawStaveBox(RenderTarget& target, RenderStates states) const
{
    RectangleShape rect(Vector2f(BOX_WIDTH, BOX_HEIGHT));
    rect.setPosition(WIDTH + PADDING, MARGIN + COORDINATE_HEIGHT);
    rect.setFillColor(Color(240, 240, 240));
    rect.setOutlineThickness(LINE_WIDTH);
    rect.setOutlineColor(Color::Black);
    target.draw(rect, states);
}

void Board::drawStave(RenderTarget& target, RenderStates states) const
{
    int padding = 10;
    wstring line = StringUtil::putStave(staves);
    Font font;
    font.loadFromFile(FONT_SONG_PATH);
    Text text;
    text.setFont(font); // font is a sf::Font
    text.setCharacterSize(LINE_HEIGHT); // in pixels, not points!
    text.setFillColor(Color::Black);
    text.setString(line.c_str());
    text.setPosition(Vector2f(WIDTH + PADDING + padding, MARGIN + COORDINATE_HEIGHT + padding));
    target.draw(text, states);
}

void Board::drawButton(RenderTarget& target, RenderStates states) const
{
    target.draw(button,states);
}
