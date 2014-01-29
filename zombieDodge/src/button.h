
#ifndef _BUTTON_H_
#define _BUTTON_H_
#include <string>
class Button
{
private:
    int m_x, m_y;            // coordinates of upper left corner of control
    int m_width, m_height;   // size of control


public:
    Button(int x, int y, int width, int height, const char* caption, std::string _buttonId);
    ~Button();
    bool IsIn( int mouseX, int mouseY );
    std::string buttonId;
    void Render();
};

#endif