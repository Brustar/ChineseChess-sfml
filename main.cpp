#include "Board.h"
#include "Game.h"
#include "StringUtil.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

int main()
{
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(VideoMode(WIDTH + CHAVE_WIDTH, HEIGHT), GAME_TITLE, Style::Close, settings);
    VideoMode mode = VideoMode::getDesktopMode();
    int sw = mode.width;
    int sh = mode.height;
    window.setPosition(Vector2i((sw - WIDTH - CHAVE_WIDTH) / 2, (sh - HEIGHT) / 2));
    window.setFramerateLimit(FRAME_RATE);
    Board board;
    Game* game = new Game(&board);
    char fen[] = STD_FEN;
    game->drawGameFromFen(fen);
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::KeyPressed)
            {
                if(event.key.control == 1)
                {
                    if (event.key.code == Keyboard::Z)
                    {
                        game->backStep();
                    }
                    if (event.key.code == Keyboard::O)
                    {
                        game->openfile(&window);
                    }
                    if (event.key.code == Keyboard::S)
                    {
                        game->savefile(NULL);
                    }
                    if (event.key.code == Keyboard::F)
                    {
                        window.create(mode, "", Style::None, settings);
                        board.setPosition((sw - WIDTH - CHAVE_WIDTH) / 2, (sh - HEIGHT) / 2);
                        window.setPosition(Vector2i(0, 0));
                    }
                }
                if (event.key.code == Keyboard::Escape)
                {
                    window.create(VideoMode(WIDTH + CHAVE_WIDTH, HEIGHT), GAME_TITLE, Style::Close, settings);
                    board.setPosition(0, 0);
                    window.setPosition(Vector2i((sw - WIDTH - CHAVE_WIDTH) / 2, (sh - HEIGHT) / 2));
                }
            }
        }

        if (Mouse::isButtonPressed(Mouse::Left))
        {
            Vector2i m = Mouse::getPosition(window);
            int offsetX = 0;
            int offsetY = 0;
            if (sw == window.getSize().x) //fullscreen
            {
                offsetX = (sw - WIDTH - CHAVE_WIDTH) / 2;
                offsetY = (sh - HEIGHT) / 2;
            }
            Point p = StringUtil::transf(m.x, m.y, offsetX, offsetY);

            bool canGO = game->containsPM(p);
            Chess chess = game->targetChess(p.row, p.col);
            if (chess.name)
            {
                if(canGO)
                {
                    game->goChess(p);
                }
                else
                {
                    if (game->canSel(chess))
                    {
                        game->addFirstTrack(p);
                        game->setDriveChess(chess);
                        vector<Point> goList = game->canGolist(chess);
                        game->setPM(goList);
                    }
                }
            }
            else
            {
                if(canGO)
                {
                    game->goChess(p);
                }
            }

        }
        window.clear(Color::White);
        window.draw(board);
        board.button.setText(board.staves.empty() ? L"载入" : L"打谱", &window);
        if(board.button.onClick(event))
        {
            game->savefile(&window);
        }
        window.display();
    }

    return 0;
}
