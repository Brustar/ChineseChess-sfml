#pragma once
#include "windef.h"
#include <string>
#include "winuser.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

#define MAX_LINE 1024

class Dialog
{
public:
    static void alert(int row, int col);
    static int confirm(string msg);
    static bool showOpenfile(RenderWindow* window,char buf[]);
    static void showSavefile(string content);
};
