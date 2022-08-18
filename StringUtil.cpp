#include "StringUtil.h"
#include <windows.h>
#include <codecvt>

bool StringUtil::isNumber(char c)
{
    return c >= 48 && c <= 57;
}

bool StringUtil::isUpper(char c)
{
    return (c >= 'A') && (c <= 'Z');
}

string StringUtil::wstringToUtf8(std::wstring& str)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t> > strCnv;
    return strCnv.to_bytes(str);
}

bool StringUtil::valid(Point p)
{
    return p.row >= 0 && p.col >= 0 && p.col < 9 && p.row < 10;
}

void StringUtil::char_to_wchar(const char* ch, std::wstring& w_str)
{
    wchar_t* wchar;
    int len = MultiByteToWideChar(CP_ACP, 0, ch, strlen(ch), NULL, 0);
    wchar = new wchar_t[len + 1];
    MultiByteToWideChar(CP_ACP, 0, ch, strlen(ch), wchar, len);
    wchar[len] = '\0';
    w_str = wchar;
    delete[]wchar;
}

wstring StringUtil::translate(char c)
{
    switch (c)
    {
    case 'r':
    case 'R':
        return L"車";
    case 'n':
    case 'N':
        return L"馬";
    case 'b':
        return L"象";
    case 'B':
        return L"相";
    case 'a':
        return L"士";
    case 'A':
        return L"仕";
    case 'c':
        return L"砲";
    case 'C':
        return L"炮";
    case 'p':
        return L"卒";
    case 'P':
        return L"兵";
    case 'k':
        return L"將";
    case 'K':
        return L"帥";

    default:
        return L"";
    }

}

wstring StringUtil::putStave(vector<wstring> staves)
{
    size_t cap = ((BOX_HEIGHT) / LINE_HEIGHT) * 2 - 8; //29
    int start = 0;
    if (staves.size() > cap)
    {
        start = ((staves.size() - 1 - cap) / 2 + 1) * 2;
    }
    wstring line;
    for (size_t i = start; i < staves.size(); i++)
    {
        if (i % 2 == 0)
        {
            line.append(to_wstring(i / 2 + 1)).append(L". ").append(staves.at(i));
        }
        else
        {
            line.append(L"  ").append(staves.at(i)).append(L"\n");
        }
    }
    return line;
}

wstring StringUtil::buildStave(char name, Point pos, Point newPos, preStave prefix)
{
    wstring stave = translate(name);
    if (isUpper(name))
    {
        stave += COORDINATE[pos.col];
        if (pos.row == newPos.row)
        {
            stave += L"平";
            stave += COORDINATE[newPos.col];
        }
        else if (pos.row > newPos.row)
        {
            stave += L"进";
        }
        else
        {
            stave += L"退";
        }
    }
    else
    {
        stave += pos.col + 1 + '0';
        if (pos.row == newPos.row)
        {
            stave += L"平";
            stave += newPos.col + 1 + '0';
        }
        else if (pos.row < newPos.row)
        {
            stave += L"进";
        }
        else
        {
            stave += L"退";
        }
    }

    if (pos.row != newPos.row)
    {
        if (name == 'N' || name == 'B' || name == 'A')
        {
            stave += COORDINATE[newPos.col];
        }
        else if (name == 'n' || name == 'b' || name == 'a')
        {
            stave += newPos.col + 1 + '0';
        }
        else
        {
            if (isUpper(name))
            {
                stave += COORDINATE[9 - abs(pos.row - newPos.row)];
            }
            else
            {
                stave += abs(pos.row - newPos.row) + '0';
            }
        }
    }

    switch (prefix)
    {
    case FRONT:
        stave = L"前" + stave.substr(0, 1) + stave.substr(2);
        break;
    case END:
        stave = L"后" + stave.substr(0, 1) + stave.substr(2);
        break;
    case MIDDLE:
        stave = L"中" + stave.substr(0, 1) + stave.substr(2);
        break;
    case NONE:
    default:
        break;
    }

    return stave;
}

Point StringUtil::transf(int x, int y, int offsetX, int offsetY)
{
    int col = (x - offsetX) / GRID_SIZE;
    int row = (y - offsetY - COORDINATE_HEIGHT) / GRID_SIZE;
    Point p;
    if(row < 10)
    {
        p.col = col;
        p.row = row;
    }
    return p;
}
