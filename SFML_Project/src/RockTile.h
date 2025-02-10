#include <SFML/Graphics.hpp>
#include "GameTile.h"

#ifndef ROCKTILE_H
#define ROCKTILE_H



using namespace sf;
using namespace std;


const string ROCK_TILE = "images/rocks_copy_2.png";

class RockTile : public GameTile {
public:
    bool isPassable;
    RockTile(Vector2f pos);
};

#endif