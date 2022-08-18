#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class Button: public Drawable
{
public:
    Button(): app(NULL), isActive(false), PreBehRel(false) {};
    virtual void draw(RenderTarget& target, RenderStates states) const;
    RenderWindow* app;//在app窗口中显示按钮
    bool isActive;//按钮是否活跃状态,这个后面会解释
    bool PreBehRel;//松开之前是否按下，这个后面会解释
    void setTextrue(String s);//设置贴图路径
    void setText(wstring text,RenderWindow* app);
    void setPosition(int x, int y);//位置
    void setScale(float x, float y);//大小
    void show();//显示按钮
    bool onClick(Event& e);//按钮响应
    Sprite s;//精灵
    Texture t;//贴图
    wstring text;
    FloatRect box;
};
