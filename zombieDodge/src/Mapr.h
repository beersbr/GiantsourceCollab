#ifndef  _MAP_R_
#define _MAP_R_
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <stdio.h>
#include <iosfwd>
#include <assert.h>
#include "Jsonator.h"
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
const int TOTAL_TILES = 188;
const int TOTAL_TILE_SPRITES = 12;
//Tile constants
const int TILE_WIDTH = 80;
const int TILE_HEIGHT = 80;


//The different tile sprites
const int TILE_RED = 0;
const int TILE_GREEN = 1;
const int TILE_BLUE = 2;
const int TILE_CENTER = 3;
const int TILE_TOP = 4;
const int TILE_TOPRIGHT = 5;
const int TILE_RIGHT = 6;
const int TILE_BOTTOMRIGHT = 7;
const int TILE_BOTTOM = 8;
const int TILE_BOTTOMLEFT = 9;
const int TILE_LEFT = 10;
const int TILE_TOPLEFT = 11;

#include "Tile.h"
class Mapr {

public:
    Mapr();
    ~Mapr();

    //Initializes position and type

    SDL_Texture* mapTexture;
    Jsonator *levelConfig;
    bool CreateMap();
    bool SetTiles(  );
    //Shows the tile
    std::vector<Tile*> tiles;

    SDL_Rect tileClips[ TOTAL_TILE_SPRITES ];

    bool TouchesWall( SDL_Rect box, Tile* tiles[] );


private:

};

#endif