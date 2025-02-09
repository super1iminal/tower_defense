#include <SFML/Graphics.hpp>
#include "GameTile.h"

#ifndef BUSHTILE_H
#define BUSHTILE_H



using namespace sf;
using namespace std;

class BushTile : public GameTile {
public:
    bool isPassable;
    BushTile(float x,float y);
};

#endif