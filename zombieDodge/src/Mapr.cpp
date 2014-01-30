#include "Mapr.h"
#include "gameEngine.h"

Mapr::Mapr() {



}

Mapr::~Mapr() {



}


bool Mapr::CreateMap() {

    bool success = true;

    mapTexture = gameEngine::getInstance()->LoadTexture("map-tiles.png");
    
    if (mapTexture == NULL) {
        printf( "Failed to load tile set texture!\n" );
        success = false; 
    }


    //Load tile map
    if( !SetTiles(  ) )
    {
        printf( "Failed to load tile set!\n" );
        success = false;
    }

    return success;

}

bool Mapr::SetTiles( )
    {
        //Success flag
        bool tilesLoaded = true;

        //The tile offsets
        int x = 0, y = 0;
        int tileCnt = 0;
        levelConfig = new Jsonator();
        levelConfig->LoadData("config/map.json");
        cJSON *mapNode = levelConfig->GetNode(NULL,"map");

         for (int i = 0 ; i < cJSON_GetArraySize(mapNode) ; i++)
            {
                cJSON * row = cJSON_GetArrayItem(mapNode, i);

                for (int v = 0 ; v < cJSON_GetArraySize(row) ; v++)
                {

                    if( ( row[v].valueint >= 0 ) && ( row[v].valueint < TOTAL_TILE_SPRITES ) )
                    {
                        Tile* tile =new Tile( x, y, row[v].valueint );
                        tiles.push_back(tile);
                        tile = nullptr;
                    }

                    x += TILE_WIDTH;

                }

                x = 0;

                //Move to the next row
                y += TILE_HEIGHT;
          }
        std::cout << "TOTAL TITLES->" << sizeof(tiles) << std::endl;
        if( tilesLoaded )
        {
            tileClips[ TILE_RED ].x = 0;
            tileClips[ TILE_RED ].y = 0;
            tileClips[ TILE_RED ].w = TILE_WIDTH;
            tileClips[ TILE_RED ].h = TILE_HEIGHT;

            tileClips[ TILE_GREEN ].x = 0;
            tileClips[ TILE_GREEN ].y = 80;
            tileClips[ TILE_GREEN ].w = TILE_WIDTH;
            tileClips[ TILE_GREEN ].h = TILE_HEIGHT;

            tileClips[ TILE_BLUE ].x = 0;
            tileClips[ TILE_BLUE ].y = 160;
            tileClips[ TILE_BLUE ].w = TILE_WIDTH;
            tileClips[ TILE_BLUE ].h = TILE_HEIGHT;

            tileClips[ TILE_TOPLEFT ].x = 80;
            tileClips[ TILE_TOPLEFT ].y = 0;
            tileClips[ TILE_TOPLEFT ].w = TILE_WIDTH;
            tileClips[ TILE_TOPLEFT ].h = TILE_HEIGHT;

            tileClips[ TILE_LEFT ].x = 80;
            tileClips[ TILE_LEFT ].y = 80;
            tileClips[ TILE_LEFT ].w = TILE_WIDTH;
            tileClips[ TILE_LEFT ].h = TILE_HEIGHT;

            tileClips[ TILE_BOTTOMLEFT ].x = 80;
            tileClips[ TILE_BOTTOMLEFT ].y = 160;
            tileClips[ TILE_BOTTOMLEFT ].w = TILE_WIDTH;
            tileClips[ TILE_BOTTOMLEFT ].h = TILE_HEIGHT;

            tileClips[ TILE_TOP ].x = 160;
            tileClips[ TILE_TOP ].y = 0;
            tileClips[ TILE_TOP ].w = TILE_WIDTH;
            tileClips[ TILE_TOP ].h = TILE_HEIGHT;

            tileClips[ TILE_CENTER ].x = 160;
            tileClips[ TILE_CENTER ].y = 80;
            tileClips[ TILE_CENTER ].w = TILE_WIDTH;
            tileClips[ TILE_CENTER ].h = TILE_HEIGHT;

            tileClips[ TILE_BOTTOM ].x = 160;
            tileClips[ TILE_BOTTOM ].y = 160;
            tileClips[ TILE_BOTTOM ].w = TILE_WIDTH;
            tileClips[ TILE_BOTTOM ].h = TILE_HEIGHT;

            tileClips[ TILE_TOPRIGHT ].x = 240;
            tileClips[ TILE_TOPRIGHT ].y = 0;
            tileClips[ TILE_TOPRIGHT ].w = TILE_WIDTH;
            tileClips[ TILE_TOPRIGHT ].h = TILE_HEIGHT;

            tileClips[ TILE_RIGHT ].x = 240;
            tileClips[ TILE_RIGHT ].y = 80;
            tileClips[ TILE_RIGHT ].w = TILE_WIDTH;
            tileClips[ TILE_RIGHT ].h = TILE_HEIGHT;

            tileClips[ TILE_BOTTOMRIGHT ].x = 240;
            tileClips[ TILE_BOTTOMRIGHT ].y = 160;
            tileClips[ TILE_BOTTOMRIGHT ].w = TILE_WIDTH;
            tileClips[ TILE_BOTTOMRIGHT ].h = TILE_HEIGHT;
        }


        //If the map was loaded fine
        return tilesLoaded;

}

bool Mapr::TouchesWall( SDL_Rect box, Tile* tiles[] )
{
    //Go through the tiles
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        //If the tile is a wall type tile
        if( ( tiles[ i ]->GetType() >= TILE_CENTER ) && ( tiles[ i ]->GetType() <= TILE_TOPLEFT ) )
        {
            //If the collision box touches the wall tile
            if( gameEngine::getInstance()->CheckCollision( box, tiles[ i ]->GetBox() ) )
            {
                return true;
            }
        }
    }

    //If no wall tiles were touched
    return false;
}