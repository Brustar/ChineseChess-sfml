#include "Button.h"
#include "../Board.h"

void Button::setTextrue(String s)
{
    this->t.loadFromFile(s);
    this->s.setTexture(this->t);
}

void Button::setText(wstring text, RenderWindow* app)
{
    this->app = app;
    isActive = true;
    VideoMode mode = VideoMode::getDesktopMode();
    int sw = mode.width;
    int sh = mode.height;
    int offsetX = 0;
    int offsetY = 0;
    if (sw == app->getSize().x) //fullscreen
    {
        offsetX = (sw - WIDTH - CHAVE_WIDTH) / 2;
        offsetY = (sh - HEIGHT) / 2;
    }
    this->box = FloatRect(WIDTH + PADDING + offsetX, BOX_HEIGHT + 2 * PADDING + offsetY, GRID_SIZE, COORDINATE_HEIGHT);
    this->text = text;
}

void Button::setPosition(int x, int y)
{
    this->s.setPosition(x, y);
}

void Button::setScale(float x, float y)
{
    this->s.setScale(x, y);
}

bool Button::onClick(Event& e)
{
    if (!isActive) //如果按钮不是活跃状态（不显示），不响应
        return false;
    bool flag = false;
    FloatRect box = this->text.empty() ? s.getGlobalBounds() : this->box; //获取按钮的有效点击范围
    if (Mouse::getPosition(*app).x >= box.left && Mouse::getPosition(*app).x <= (box.left + box.width) && Mouse::getPosition(*app).y >= box.top && Mouse::getPosition(*app).y <= (box.top + box.height))
    {
        if (e.type == Event::MouseButtonReleased && e.mouseButton.button == Mouse::Left && PreBehRel)
        {
            this->PreBehRel = false;//要先按下再松开才返回true，置于为什么要判断先按下，后面会讲
            flag = true;
        }
        else
            flag = false;
        if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left)
        {
            this->s.setColor(Color(125, 125, 0, 255));//按钮按下时的颜色和不透明度
            this->PreBehRel = true;
        }
        else
            this->s.setColor(Color(125, 125, 0, 100));//鼠标指着按钮但未按下时的颜色和不透明度
    }
    else
        this->s.setColor(Color(255, 255, 255, 255)); //默认状态的按钮颜色
    return flag;
}

void Button::draw(RenderTarget& target, RenderStates states) const
{
    RectangleShape rectangle(Vector2f(GRID_SIZE, COORDINATE_HEIGHT));
    rectangle.setPosition(WIDTH + PADDING, BOX_HEIGHT + 2 * PADDING);
    rectangle.setFillColor(Color::White);
    rectangle.setOutlineThickness(LINE_WIDTH / 2);
    rectangle.setOutlineColor(Color::Black);
    target.draw(rectangle, states);

    Font font;
    font.loadFromFile(FONT_SONG_PATH);
    Text text;
    text.setFont(font); // font is a sf::Font
    text.setCharacterSize(LINE_HEIGHT); // in pixels, not points!
    text.setFillColor(Color::Black);
    text.setString(this->text.c_str());
    text.setPosition(Vector2f(WIDTH + PADDING + 15, BOX_HEIGHT + 2 * PADDING + 3));
    target.draw(text, states);
}

void Button::show()
{
    isActive = true;//若要显示，则为活跃状态
    if(this->text.empty())
    {
        (*app).draw(s);
    }
    else
    {
        (*app).draw(*this);
    }
}
