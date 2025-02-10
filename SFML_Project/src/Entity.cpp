#include "Entity.h"
using namespace sf;
using namespace std;


Entity::Entity(string textureName, Vector2f pos, Vector2f scale, IntRect textureRect) {
    if(!setUpSprite(textureName, scale, textureRect)){
        return;
    }

    sprite.setPosition(pos.x, pos.y);
};

bool Entity::setUpSprite(string textureName, Vector2f scale, IntRect textureRect) {
    if(!texture.loadFromFile(textureName)){
        return false;
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setScale(scale);

    if (textureRect.width == 0 || textureRect.height == 0) {
        sprite.setTextureRect(IntRect(0, 0, texture.getSize().x, texture.getSize().y));
        return true;
    } else {
        sprite.setTextureRect(textureRect);
        return true;
    }
    return false;
}