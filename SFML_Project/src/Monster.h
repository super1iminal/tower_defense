#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Entity.h"

#ifndef MOSTER_H
#define MONSTER_H

using namespace sf;
using namespace std;

const string MONSTER_TEXTURE = "images/frame-1.png";

class Monster : public Entity{
public:
    Monster(Vector2f pos, vector<Vector2i>& path);
    float bobbingAmplitude;    // Amplitude of bobbing
    float bobbingSpeed;        // Speed of bobbing
    float bobbingOffset;       // Current offset of bobbing
    
    float animationFrameTime;  // Time between frame updates
    float lastFrameTime;      // Time tracker for frame switching
    int currentFrame;          // Keeps track of the current animation frame (0 or 1)
    size_t currentTarget = 0;  // Index of the current target point in the path
    vector<sf::Vector2i> path;
    int speed = 2;
    
    int pathLength;
    void moveToNextPoint(float deltaTime);

    void draw(sf::RenderWindow& window);
};

#endif
