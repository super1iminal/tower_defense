
#include <SFML/Graphics.hpp>
#include "GameTile.h"

#ifndef TREETILE_H
#define TREETILE_H

using namespace sf;
using namespace std;

const string TREE_TILE = "images/trees1.png";

class TreeTile : public GameTile {
public:
    bool isPassable;
    TreeTile(Vector2f pos);
};

#endif