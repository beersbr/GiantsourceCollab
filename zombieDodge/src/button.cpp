#include "button.h"

Button::Button(int x, int y, int width, int height, const char* caption,std::string _buttonId)
    {
        m_x = x;
        m_y = y;
        m_width = width;
        m_height = height;
        buttonId = _buttonId;
        // also store caption in variable of same type you're using now for button text
    }

bool Button::IsIn( int mouseX, int mouseY )
    {
        if (((mouseX > m_x) && (mouseX < m_x + m_width))
                && ((mouseY > m_y) && (mouseY < m_y + m_height ) ) ) {
            return true;
        } else {
            return false;
        }
    }

void Button::Render()
    {
        // use the same code you use now to render the button in OpenGL/SDL
    }

Button::~Button() {


}