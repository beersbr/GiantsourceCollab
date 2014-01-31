#ifndef  _TILE_R_
#define _TILE_R_
#include <SDL2/SDL.h>
class Tile
{
public:
    //Initializes position and type
    Tile( int x, int y, int tileType );

    //Shows the tile
    void Render( SDL_Rect& camera );

    //Get the tile type
    int GetType();

    //Get the collision box
    SDL_Rect GetBox();

private:
    //The attributes of the tile
    SDL_Rect tileBox;

    //The tile type
    int tileType;
};

#endif