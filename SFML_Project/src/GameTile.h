#include <SFML/Graphics.hpp>
#include "Entity.h"

#ifndef GAMETILE_H
#define GAMETILE_H

using namespace sf;
using namespace std;

class GameTile : public Entity {
public:
    Vector2f pos;
    Sprite sprite;
    Texture texture;
    GameTile(string, Vector2f);
    //void GameTile::draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif

























/*
#include <SFML/Graphics.hpp>

#ifndef GAMETILE_H
#define GAMETILE_H

using namespace sf;
using namespace std;

class gameTile{
public:
    bool isPassable;
    bool isExit;
    Vector2f pos;
    Texture texture;
    Sprite sprite;
    gameTile(string,float,float,bool,bool);
    bool setUpSprite(string);
};

#endif
*/