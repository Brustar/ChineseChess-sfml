#pragma once
#include "Chess.h"
#include "Board.h"
#include "StringUtil.h"
#include "Dialog.h"
#include <vector>
#include <stack>
using namespace std;

#define MAX_LINE 1024
#define FRAME_RATE 12

class Game
{
private:
    stack<vector<Chess>> steps;
    Board *board;
    Chess driveChess;
    bool redGo;

    void removeChess(Chess chess);
    void removePoint(vector<Point>* v, Point p);
    bool advisorMove(Chess chess, int row, int col);
    bool kingMove(Chess chess, int row, int col);
    bool knightMove(Chess chess, int row, int col);
    bool cannonMove(Chess chess, int row, int col);
    bool bishopMove(Chess chess, int row, int col);
    bool rookMove(Chess chess, int row, int col);
    bool pawnMove(Chess chess, int row, int col);
    preStave buildPrefix(Chess chess);
    int pmSize();
    int trackSize();
    void clearTracks();
    void clearChaves();
    Point trackItem(int index);
    Point pmItem(int index);
    vector<Point> clearAttack(vector<Point> v, Chess chess);
    bool canMove(Chess chess, int row, int col);
    bool win(Chess chess);
    void clearPM();
    bool step(Chess chess, int row, int col);
    bool emptyOrCanEat(Chess chess, int row, int col);
    bool canEat(Chess chess, int row, int col);
    bool noneChess(int row, int col);

    bool validKnightMove(Chess chess, int row, int col);
    bool validBishopMove(Chess chess, int row, int col);
    bool validRookMove(Chess chess, int row, int col);
    bool validCannonMove(Chess chess, int row, int col);
    int hasBetweenChess(int same, int start, int end, bool vertical);
    bool canAttack(Chess enemy, int row, int col);
    bool kingFaceAttack(Chess chess, int row, int col);
    Point attackKingPos(Chess enemy, int row, int col, Chess chess);
    Chess kingChess(Chess chess);

public:
    Game(Board *board);
    ~Game();
    void clearChesses();
    void addChess(Chess chess);
    void addPM(Point p);
    void addFirstTrack(Point p);
    void addSecondTrack(Point p);
    bool containsPM(Point p);
    void removeChess(Point p);
    Chess targetChess(int row, int col);
    void setDriveChess(Chess chess);
    void goChess(Point p);
    bool canSel(Chess chess);
    vector<Point> canGolist(Chess chess);
    void setPM(vector<Point> goList);
    void backStep();
    void openfile(RenderWindow* window);
    void savefile(RenderWindow* window);
    void drawGameFromFen(char fen[]);

    void appendStaves(wstring stave);
};

