#pragma once
#include <SFML/Graphics.hpp>
#include "LineShape.h"
#include "Chess.h"
#include "Button.h"
#include <string>
#include <vector>
#include <utility>

using namespace sf;
using namespace std;

#define WIDTH 540
#define HEIGHT 650

#define GRID_SIZE 60
#define PADDING 30
#define MARGIN PADDING * 2 / 3
#define COORDINATE_HEIGHT 25

#define BOX_WIDTH 200
#define BOX_HEIGHT 9 * GRID_SIZE
#define LINE_HEIGHT 16
#define LINE_WIDTH 2
#define CHAVE_WIDTH 250
#define STD_FEN "rnbakabnr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RNBAKABNR"
#define COORDINATE L"九八七六五四三二一"
#define GAME_TITLE L"中国象棋谱"
#define FONT_PATH "c:/Windows/Fonts/simli.ttf"
#define FONT_SONG_PATH "c:/Windows/Fonts/simhei.ttf"

struct Point
{
    int row = -1;
    int col = -1;

    bool operator==(const Point& p)
    {
        if (this->row == p.row && this->col == p.col)
        {
            return true;
        }
        return false;
    }
};

class Board: public Drawable, public Transformable
{
public:
    pair<Point, Point> tracks;
    vector<Point> passibleMove;
    vector<Chess> map;
    vector<wstring> staves;
    Button button;

private:
    void drawDiagonal(RenderTarget& target, RenderStates states) const;
    void drawLine(RenderTarget& target, RenderStates states, int x, int y, int x1, int y1) const;
    void track(RenderTarget& target, RenderStates states, int row, int col) const;
    void drawTracks(RenderTarget& target, RenderStates states) const;
    void drawStep(RenderTarget& target, RenderStates states) const;
    void drawChesses(RenderTarget& target, RenderStates states) const;
    void drawDecorate(RenderTarget& target, RenderStates states) const;
    void drawCoordinate(RenderTarget& target, RenderStates states) const;
    void drawStaveBox(RenderTarget& target, RenderStates states) const;
    void drawStave(RenderTarget& target, RenderStates states) const;
    void drawButton(RenderTarget& target, RenderStates states) const;
    virtual void draw(RenderTarget& target, RenderStates states) const;
};
