#ifndef  __GAMESTATE_H
#define __GAMESTATE_H

#include "gameEngine.h"

class GameState {
public:
    GameState(int _stateId, std::string _name, int _key);
    int stateId, key;
    std::string name;
    std::string background;
    virtual void Draw() = 0;
    virtual void HandleInput(SDL_Event& event) = 0;
    virtual bool LoadResources() = 0;
    virtual void Update() = 0;
    virtual bool Setup() =0;

private:


};
#endif