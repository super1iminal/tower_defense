#include "GameTile.h"
using namespace sf;
using namespace std;

GameTile::GameTile(string textureName, float x, float y){
    if(!setUpSprite(textureName)){
        return;
    }
    pos = Vector2f(x,y);
    sprite.setPosition(pos);
}

bool GameTile::setUpSprite(string textureName){
    if(!texture.loadFromFile(textureName)){
        return false;
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setScale(1.f,1.f);
    sprite.setTextureRect(IntRect(0,0,50,50));
    return true;
}
/*
void GameTile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}
*/


























/*#include "gameTile.h"
using namespace sf;
using namespace std;

gameTile::gameTile(string textureName, float x, float y, bool passable, bool exit){
    if(!setUpSprite(textureName)){
        return;
    }
    pos = sf::Vector2f(x,y);
    sprite.setPosition(pos);
    isPassable = passable;
    isExit = exit;
}

bool gameTile::setUpSprite(string textureName){
    if(!texture.loadFromFile(textureName)){
        return false;
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setScale(1.f,1.f);
    sprite.setTextureRect(IntRect(0,0,50,50));
    return true;
}*/