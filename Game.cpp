#include "Game.h"
#include "Math.h"

Game::Game(Board *board)
{
    this->board = board;
    this->steps = {};
    this->redGo = true;
}

Game::~Game()
{
    delete& this->steps;
}

void Game::addChess(Chess chess)
{
    for (Chess ch : this->board->map)
    {
        if (ch.row == chess.row && ch.col == chess.col)
        {
            removeChess(ch);
        }
    }
    this->board->map.push_back(chess);
}

void Game::removeChess(Chess chess)
{
    auto itor = find(this->board->map.begin(), this->board->map.end(), chess);
    if (itor != this->board->map.end())
    {
        this->board->map.erase(itor);
    }
}

void Game::removeChess(Point p)
{
    Chess chess = targetChess(p.row, p.col);
    if (!noneChess(p.row, p.col))
    {
        removeChess(chess);
    }
}

void Game::addPM(Point p)
{
    this->board->passibleMove.push_back(p);
}

void Game::removePoint(vector<Point>* v, Point p)
{
    vector<Point>::iterator it = v->begin();
    for (; it != v->end();)
    {
        if ((*it) == p)
        {
            vector<Point>::iterator tmp = it;
            it = v->erase(tmp);
        }
        else
        {
            it++;
        }
    }
}

int Game::pmSize()
{
    return this->board->passibleMove.size();
}

Point Game::pmItem(int index)
{
    return this->board->passibleMove[index];
}

void Game::clearPM()
{
    this->board->passibleMove.clear();
    vector<Point>(this->board->passibleMove).swap(this->board->passibleMove);
}

void Game::clearChaves()
{
    this->board->staves.clear();
    vector<wstring>(this->board->staves).swap(this->board->staves);
}

bool Game::containsPM(Point p)
{
    return find(this->board->passibleMove.begin(), this->board->passibleMove.end(), p) != this->board->passibleMove.end();
}

void Game::clearChesses()
{
    this->board->map.clear();
    vector<Chess>(this->board->map).swap(this->board->map);
    this->redGo = true;
    clearTracks();
    clearPM();
    clearChaves();
}

void Game::clearTracks()
{
    this->board->tracks.first = {-1};
    this->board->tracks.second = {-1};
}

vector<Point> Game::clearAttack(vector<Point> v, Chess chess)
{
    vector<Point> attackingPos = {};
    for (Point pt: v)
    {
        for (Chess enemy : this->board->map)
        {
            if (enemy.isRed != chess.isRed)
            {
                Point p = attackKingPos(enemy, pt.row, pt.col, chess);
                if (p.row != -1 && p.col != -1)
                    attackingPos.push_back(p);
            }
        }
    }
    for (Point p: attackingPos)
    {
        removePoint(&v, p);
    }
    return v;
}

bool Game::canMove(Chess chess, int row, int col)
{
    switch (chess.name)
    {
    case 'p':
    case 'P':
        return pawnMove(chess, row, col);
    case 'c':
    case 'C':
        return cannonMove(chess, row, col);
    case 'r':
    case 'R':
        return rookMove(chess, row, col);
    case 'n':
    case 'N':
        return knightMove(chess, row, col);
    case 'b':
    case 'B':
        return bishopMove(chess, row, col);
    case 'a':
    case 'A':
        return advisorMove(chess, row, col);
    case 'k':
    case 'K':
        return kingMove(chess, row, col);
    default:
        break;
    }
    return false;
}

bool Game::step(Chess chess, int row, int col)
{
    if (chess.col == col && abs(chess.row - row) == 1)
        return true;
    if (chess.row == row && abs(chess.col - col) == 1)
        return true;

    return false;
}

Chess Game::targetChess(int row, int col)
{
    for (Chess chess : this->board->map)
    {
        if (chess.col == col && chess.row == row)
            return chess;
    }
    return { -1, -1, 0 };
}

bool Game::canEat(Chess chess, int row, int col)
{
    Chess target = targetChess(row, col);
    if (!noneChess(row, col))
    {
        if (chess.isRed != target.isRed)
        {
            return true;
        }
    }
    return false;
}

bool Game::noneChess(int row, int col)
{
    Chess target = targetChess(row, col);
    if (!target.name)
    {
        return true;
    }
    return false;
}

bool Game::emptyOrCanEat(Chess chess, int row, int col)
{
    return noneChess(row, col) || canEat(chess, row, col);
}

bool Game::validKnightMove(Chess chess, int row, int col)
{
    if (abs(chess.col - col) == 1)
    {
        if (chess.row - row == 2)
        {
            if (noneChess(row + 1, chess.col))
                return true;
        }
        if (chess.row - row == -2)
        {
            if (noneChess(row - 1, chess.col))
                return true;
        }
    }
    if (abs(chess.row - row) == 1)
    {
        if (chess.col - col == 2)
        {
            if (noneChess(chess.row, col + 1))
                return true;
        }
        if (chess.col - col == -2)
        {
            if (noneChess(chess.row, col - 1))
                return true;
        }
    }
    return false;
}

bool Game::validBishopMove(Chess chess, int row, int col)
{
    if (chess.col > col)
    {
        if (chess.row > row)
        {
            if (noneChess(row + 1, col + 1))
            {
                return true;
            }
        }
        if (chess.row < row)
        {
            if (noneChess(row - 1, col + 1))
            {
                return true;
            }
        }
    }
    if (chess.col < col)
    {
        if (chess.row > row)
        {
            if (noneChess(row + 1, col - 1))
            {
                return true;
            }
        }
        if (chess.row < row)
        {
            if (noneChess(row - 1, col - 1))
            {
                return true;
            }
        }
    }
    return false;
}

int Game::hasBetweenChess(int same, int start, int end, bool vertical = true)
{
    for (int i = start + 1; i < end; i++)
    {
        if (vertical)
        {
            if (!noneChess(i, same))
            {
                return i;
            }
        }
        else
        {
            if (!noneChess(same, i))
            {
                return i;
            }
        }
    }
    return 0;
}

bool Game::validRookMove(Chess chess, int row, int col)
{
    if (chess.row == row)
    {
        if (chess.col != col)
        {
            return hasBetweenChess(row, min(col, chess.col), max(col, chess.col), false) == 0;
        }
    }
    if (chess.col == col)
    {
        if (chess.row != row)
        {
            return hasBetweenChess(col, min(row, chess.row), max(row, chess.row)) == 0;
        }
    }
    return false;
}

bool Game::validCannonMove(Chess chess, int row, int col)
{
    if (canEat(chess, row, col))
    {
        if (chess.col == col)
        {
            if (abs(chess.row - row) > 1)
            {
                int i = hasBetweenChess(col, min(row, chess.row), max(row, chess.row));
                if (i > 0)
                    return hasBetweenChess(col, i, max(row, chess.row)) == 0;
            }
        }
        if (chess.row == row)
        {
            if (abs(chess.col - col) > 1)
            {
                int i = hasBetweenChess(row, min(col, chess.col), max(col, chess.col), false);
                if (i > 0)
                    return hasBetweenChess(row, i, max(col, chess.col), false) == 0;
            }
        }
    }
    return false;
}

bool Game::knightMove(Chess chess, int row, int col)
{
    if (emptyOrCanEat(chess, row, col))
    {
        if (pow(chess.col - col, 2) + pow(chess.row - row, 2) == 5)
        {
            return validKnightMove(chess, row, col);
        }
    }
    return false;
}

bool Game::advisorMove(Chess chess, int row, int col)
{
    if (emptyOrCanEat(chess, row, col))
    {
        if (chess.isRed)
        {
            if (chess.row == 7 or chess.row == 9)
            {
                if (row == 8 && col == 4)
                    return true;
            }
            if (chess.row == 8)
            {
                if (row == 7 && col == 3)
                    return true;
                if (row == 9 && col == 3)
                    return true;
                if (row == 7 && col == 5)
                    return true;
                if (row == 9 && col == 5)
                    return true;
            }
        }
        else
        {
            if (chess.row == 2 || chess.row == 0)
            {
                if (row == 1 && col == 4)
                    return true;
            }
            if (chess.row == 1)
            {
                if (row == 2 && col == 3)
                    return true;
                if (row == 0 && col == 3)
                    return true;
                if (row == 2 && col == 5)
                    return true;
                if (row == 0 && col == 5)
                    return true;
            }
        }
    }
    return false;
}

bool Game::kingMove(Chess chess, int row, int col)
{
    if (emptyOrCanEat(chess, row, col))
    {
        if (chess.isRed)
        {
            if (row < 7 || col < 3 || col > 5)
                return false;
            else
            {
                return step(chess, row, col);
            }
        }
        else
        {
            if (row > 2 || col < 3 || col > 5)
                return false;
            else
            {
                return step(chess, row, col);
            }
        }
    }
    return false;
}

bool Game::cannonMove(Chess chess, int row, int col)
{
    if (noneChess(row, col))
    {
        if (chess.col == col && chess.row != row)
            return hasBetweenChess(col, min(row, chess.row), max(row, chess.row)) == 0;
        if (chess.col != col && chess.row == row)
            return hasBetweenChess(row, min(col, chess.col), max(col, chess.col), false) == 0;
    }
    else
    {
        if (chess.col == col && chess.row != row)
            return validCannonMove(chess, row, col);
        if (chess.col != col && chess.row == row)
            return validCannonMove(chess, row, col);
    }
    return false;
}

bool Game::bishopMove(Chess chess, int row, int col)
{
    if (emptyOrCanEat(chess, row, col))
    {
        if (chess.isRed)
        {
            if (row > 4)
            {
                if (chess.col - col == 2 && chess.row - row == 2)
                    return validBishopMove(chess, row, col);
                if (chess.col - col == -2 && chess.row - row == -2)
                    return validBishopMove(chess, row, col);
                if (chess.col - col == -2 && chess.row - row == 2)
                    return validBishopMove(chess, row, col);
                if (chess.col - col == 2 && chess.row - row == -2)
                    return validBishopMove(chess, row, col);
            }
        }
        else
        {
            if (row < 5)
            {
                if (chess.col - col == 2 && chess.row - row == 2)
                    return validBishopMove(chess, row, col);
                if (chess.col - col == -2 && chess.row - row == -2)
                    return validBishopMove(chess, row, col);
                if (chess.col - col == -2 && chess.row - row == 2)
                    return validBishopMove(chess, row, col);
                if (chess.col - col == 2 && chess.row - row == -2)
                    return validBishopMove(chess, row, col);
            }
        }
    }
    return false;
}

bool Game::rookMove(Chess chess, int row, int col)
{
    if (emptyOrCanEat(chess, row, col))
    {
        if (validRookMove(chess, row, col))
        {
            if (chess.row == row && chess.col != col)
                return true;
            if (chess.row != row && chess.col == col)
                return true;
        }
    }
    return false;
}

bool Game::pawnMove(Chess chess, int row, int col)
{
    if (emptyOrCanEat(chess, row, col))
    {
        if (chess.isRed)
        {
            if (chess.row > row)
            {
                return chess.col == col && chess.row - row == 1;
            }
            if (chess.row == row)
            {
                if (row < 5)
                    return step(chess, row, col);
            }
        }
        else
        {
            if (chess.row < row)
            {
                return chess.col == col && row - chess.row == 1;
            }
            if (chess.row == row)
            {
                if (row > 4)
                    return step(chess, row, col);
            }
        }
    }
    return false;
}

Chess Game::kingChess(Chess chess)
{
    for (Chess king : this->board->map)
    {
        if (chess.isRed)
        {
            if (king.name == 'k')
            {
                return king;
            }
        }
        else
        {
            if (king.name == 'K')
            {
                return king;
            }
        }
    }
    return {};
}

bool Game::kingFaceAttack(Chess chess, int row, int col)
{
    if (chess.col == col)
    {
        if (!hasBetweenChess(col, min(row, chess.row), max(row, chess.row)))
        {
            return true;
        }
    }
    return false;
}

bool Game::canAttack(Chess enemy, int row, int col)
{
    switch (enemy.name)
    {
    case 'p':
    case 'P':
        return pawnMove(enemy, row, col);
    case 'c':
    case 'C':
        return cannonMove(enemy, row, col);
    case 'r':
    case 'R':
        return rookMove(enemy, row, col);
    case 'n':
    case 'N':
        return knightMove(enemy, row, col);
    case 'b':
    case 'B':
    case 'a':
    case 'A':
        break;
    case 'k':
    case 'K':
        return kingFaceAttack(enemy, row, col);
    default:
        break;
    }
    return false;
}

//要被将军状态下的Point
Point Game::attackKingPos(Chess enemy, int row, int col, Chess chess)
{
    Chess king = kingChess(enemy);
    Point p = { -1, -1 };
    int krow = king.row;
    int kcol = king.col;
    vector<Chess> chesses = this->board->map;
    if (chess.name == 'k' || chess.name == 'K')
    {
        Chess temp = targetChess(row, col);
        if (!noneChess(row, col))
        {
            this->removeChess(temp);
        }
        else
        {
            this->removeChess(chess);
        }
        chess.col = col;
        chess.row = row;
        this->addChess(chess);
        if (canAttack(enemy, row, col))
        {
            p.row = row;
            p.col = col;
        }
    }
    else
    {
        this->removeChess(chess);
        chess.col = col;
        chess.row = row;
        this->addChess(chess);
        if (canAttack(enemy, krow, kcol))
        {
            //如果可以吃掉正在将军的敌棋,则不用清除
            if (!canEat(chess, row, col))
            {
                if (enemy.row != row || enemy.col != col)
                {
                    p.row = row;
                    p.col = col;
                }
            }
            else
            {
                Chess eat = targetChess(row, col);
                //正在将军的棋子不能清除
                if (!canAttack(eat, krow, kcol))
                {
                    p.row = row;
                    p.col = col;
                }
            }
        }
    }
    this->board->map = chesses;
    return p;
}

void Game::addFirstTrack(Point p)
{
    clearTracks();
    if (!noneChess(p.row, p.col))
    {
        this->board->tracks.first = p;
    }
}

void Game::addSecondTrack(Point p)
{
    if (noneChess(p.row, p.col))
    {
        this->board->tracks.second = p;
    }
    else
    {
        this->board->tracks.first = p;
    }
    this->clearPM();
}

void Game::setDriveChess(Chess chess)
{
    this->driveChess = chess;
}

preStave Game::buildPrefix(Chess chess)
{
    vector<Chess> temp = {};
    char name = chess.name;
    if (name == 'K' || name == 'k' || name == 'a' || name == 'A' || name == 'B' || name == 'b')
    {
        return NONE;
    }
    for (Chess other : this->board->map)
    {
        if (other.name == chess.name)
        {
            if (other.col == chess.col && other.row != chess.row)
            {
                temp.push_back(other);
            }
        }
    }

    int ret = temp.size();
    if (ret == 0)
    {
        return NONE;
    }
    else if (ret == 1)
    {
        Chess other = temp.at(0);
        if (chess.row > other.row)
        {
            if (StringUtil::isUpper(chess.name))
            {
                return END;
            }
            else
            {
                return FRONT;
            }
        }
        else
        {
            if (StringUtil::isUpper(chess.name))
            {
                return FRONT;
            }
            else
            {
                return END;
            }
        }
    }
    else if (ret == 2)
    {
        Chess first = temp.at(0);
        Chess second = temp.at(1);
        if (chess.row < first.row && chess.row < second.row)
        {
            if (StringUtil::isUpper(chess.name))
            {
                return FRONT;
            }
            else
            {
                return END;
            }
        }
        else if (chess.row < max(first.row, second.row) && chess.row > min(first.row, second.row))
        {
            return MIDDLE;
        }
        else
        {
            if (StringUtil::isUpper(chess.name))
            {
                return END;
            }
            else
            {
                return FRONT;
            }
        }
    }
    return NONE;
}

void Game::appendStaves(wstring stave)
{
    this->board->staves.push_back(stave);
}

void Game::goChess(Point p)
{
    addSecondTrack(p);
    Chess chess = this->driveChess;
    preStave prefix = buildPrefix(chess);
    wstring stave = StringUtil::buildStave(chess.name, { chess.row, chess.col }, p, prefix);
    appendStaves(stave);
    //eat chess
    this->removeChess(chess);
    chess.col = p.col;
    chess.row = p.row;
    this->addChess(chess);

    this->redGo = !this->redGo;
    this->steps.push(this->board->map);
    if (win(chess))
    {
        Chess king = kingChess(chess);
        king.dead = true;
        this->addChess(king);
        wstring msg = this->redGo ? L"黑" : L"红";
        wstring staves;
        appendStaves(staves.append(msg).append(L"胜!"));
        msg.append(L"方胜利,要重新选择排局吗?");
        if (Dialog::confirm(StringUtil::wstringToUtf8(msg)) == IDYES)
        {
            openfile(NULL);
        }
    }
}

bool Game::canSel(Chess chess)
{
    return chess.isRed == this->redGo;
}

vector<Point> Game::canGolist(Chess chess)
{
    vector<Point> goList = {};
    for (int col = 0; col < 9; col++)
    {
        for (int row = 0; row < 10; row++)
        {
            if (canMove(chess, row, col))
            {
                Point p;
                p.col = col;
                p.row = row;
                goList.push_back(p);
            }
        }
    }
    return clearAttack(goList, chess);
}

bool Game::win(Chess chess)
{
    for (Chess enemy : this->board->map)
    {
        if (enemy.isRed != chess.isRed)
        {
            vector<Point> goList = canGolist(enemy);
            if (goList.size() > 0)
                return false;
        }
    }
    return true;
}

void Game::setPM(vector<Point> goList)
{
    clearPM();
    this->board->passibleMove.insert(this->board->passibleMove.end(), goList.begin(), goList.end());
}

void Game::drawGameFromFen(char fen[])
{
    clearChesses();
    const char* split = "/";
    char* p;
    char* buf = NULL;
    p = strtok_s(fen, split, &buf);
    int y = 0;
    while (p != NULL)
    {
        int x = 0;
        for (size_t i = 0; i < strlen(p); i++)
        {
            if (StringUtil::isNumber(p[i]))
            {
                x += int(p[i] - '0') - 1;
            }
            else
            {
                Chess* chess = new Chess(x + i, y, p[i]);
                addChess(*chess);
            }
        }
        p = strtok_s(NULL, split, &buf);
        y++;
    }
    this->steps.push(this->board->map);
}

void Game::openfile(RenderWindow* window)
{
    char buf[MAX_LINE];
    if(Dialog::showOpenfile(window,buf))
    {
        drawGameFromFen(buf);
    }
}

void Game::savefile(RenderWindow* window)
{
    if (this->board->staves.empty())
    {
        openfile(window);
        return;
    }
    wstring content = StringUtil::putStave(this->board->staves);
    Dialog::showSavefile(StringUtil::wstringToUtf8(content));
}

void Game::backStep()
{
    if (this->steps.size() > 1)
    {
        this->steps.pop();
        this->board->map = this->steps.top();
        this->board->staves.pop_back();
        clearTracks();
        this->redGo = !this->redGo;
    }
}
