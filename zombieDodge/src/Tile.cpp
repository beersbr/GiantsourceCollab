#include "Tile.h"
#include "gameEngine.h"
Tile::Tile( int x, int y, int _tileType )
{
    //Get the offsets
    tileBox.x = x;
    tileBox.y = y;

    //Set the collision box
    tileBox.w = TILE_WIDTH;
    tileBox.h = TILE_HEIGHT;

    //Get the tile type
    tileType = _tileType;
}

void Tile::Render( SDL_Rect& camera )
{

    //If the tile is on screen
    if( gameEngine::getInstance()->CheckCollision( camera, tileBox ) )
    {
        //Show the tile
        gameEngine::getInstance()->Render(gameEngine::getInstance()->levelMap->mapTexture, tileBox.x -  gameEngine::getInstance()->camera.x, tileBox.y -  gameEngine::getInstance()->camera.y,gameEngine::getInstance()->levelMap->tileClips[ tileType ].w ,gameEngine::getInstance()->levelMap->tileClips[ tileType ].h,&gameEngine::getInstance()->levelMap->tileClips[ tileType ],NULL,NULL,SDL_FLIP_NONE );
    }
}

int Tile::GetType()
{
    return tileType;
}

SDL_Rect Tile::GetBox()
{
    return tileBox;
}
