#include <SFML/Graphics.hpp>

#ifndef ENTITY_H
#define ENTITY_H

using namespace sf;
using namespace std;

class Entity{
    public:
    Entity(string textureName, Vector2f pos, Vector2f scale = {1.f, 1.f}, IntRect textureRect = IntRect(0, 0, 0, 0));
    Sprite sprite;
    Texture texture;
    Vector2f pos;
    private:
    protected:
    bool setUpSprite(string textureName, Vector2f scale = {1.f, 1.f}, IntRect textureRect = IntRect(0, 0, 0, 0));
};



#endif