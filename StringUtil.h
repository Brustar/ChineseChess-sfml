#pragma once
#include "Board.h"
#include <tchar.h>
#include <string>
#include <vector>
using namespace std;

#define COORDINATE L"九八七六五四三二一"

enum preStave
{
    NONE = 0,
    FRONT,
    MIDDLE,
    END
};

class StringUtil
{
public:
    static bool isNumber(char c);
    static bool isUpper(char c);
    static bool valid(Point p);
    static string wstringToUtf8(std::wstring& str);
    static void char_to_wchar(const char* ch, std::wstring& w_str);
    static wstring translate(char c);
    static wstring putStave(vector<wstring>);
    static wstring buildStave(char name, Point pos, Point newPos, preStave prefix);
    static Point transf(int x, int y, int offsetX, int offsetY);
};
