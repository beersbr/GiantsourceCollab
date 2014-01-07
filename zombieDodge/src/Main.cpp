#include <iostream>

#include <SDL2/SDL.h>

// This was taken from a tutorial website as a test. make sure it runs :D

namespace game
{
    class Vector
    {
    public:
        Vector(const float x = 0, const float y = 0, const float z = 0)
        {
            this->x = x; this->y = y; this->z = z;
        }

        Vector(const Vector &v)
        {
            this->x = v.x; this->y = v.y; this->z = v.z;
        }

        Vector& operator+(const Vector &v) const
        {
            Vector *rv = new Vector();
            rv->x = this->x + v.x; rv->y = this->y + v.y; rv->z = this->z + v.z;
            return *rv;
        }

        Vector& operator+=(const Vector &v)
        {
            this->x += v.x; this->y += v.y; this->z += v.z;
            return *this;
        }

        Vector& operator-(const Vector &v) const
        {
            Vector *rv = new Vector();
            rv->x = this->x - v.x; rv->y = this->y - v.y; rv->z = this->z - v.z;
            return *rv;
        }

        Vector& operator-=(const Vector &v)
        {
            this->x -= v.x; this->y -= v.y; this->z -= v.z;
            return *this;
        }

        Vector& operator*(const Vector &v) const
        {
            Vector *rv = new Vector();
            rv->x = this->x * v.x; rv->y = this->y * v.y; rv->z = this->z * v.z;
            return *rv;
        }

        Vector& operator*=(const Vector &v)
        {
            this->x *= v.x; this->y *= v.y; this->z *= v.z;
            return *this;
        }

        Vector& operator*(const float s) const
        {
            Vector *rv = new Vector();
            rv->x = this->x * s; rv->y = this->y * s; rv->z = this->z * s;
            return *rv;
        }

        Vector& operator*=(const float s)
        {
            this->x *= s; this->y *= s; this->z *= s;
            return *this;
        }

        float x, y, z;
    };

    typedef Vector vector;

    class Entity
    {
    public:
        vector pos;
    };

}

int main(int argc, char * arg[])
{
    // init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "ERROR SDL_Init" << std::endl;
        
        return -1;
    }

    // create a window
    SDL_Window * window = SDL_CreateWindow(
                                           "SDL 2 window",             // window title
                                           SDL_WINDOWPOS_CENTERED,     // x position, centered
                                           SDL_WINDOWPOS_CENTERED,     // y position, centered
                                           640,                        // width, in pixels
                                           480,                        // height, in pixels
                                           SDL_WINDOW_OPENGL           // flags
                                           );
    
    // wait 5 secs
    SDL_Delay(5000);
    
    // clean up
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}