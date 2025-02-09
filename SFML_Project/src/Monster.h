#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#ifndef MOSTER_H
#define MONSTER_H

using namespace sf;
using namespace std;

class Monster {
public:
    float bobbingAmplitude;    // Amplitude of bobbing
    float bobbingSpeed;        // Speed of bobbing
    float bobbingOffset;       // Current offset of bobbing
    
    float animationFrameTime;  // Time between frame updates
    float lastFrameTime;      // Time tracker for frame switching
    int currentFrame;          // Keeps track of the current animation frame (0 or 1)
    Vector2f pos;
    size_t currentTarget = 0;  // Index of the current target point in the path
    vector<sf::Vector2i> path;
    int speed = 2;
    Sprite sprite;
    Texture texture;
    Monster(float x, float y, vector<Vector2i>& path);
    bool setUpSprite(string);
    int pathLength;
    Monster(const vector<Vector2i>& path);  // Constructor to pass the pat
    void moveToNextPoint(float deltaTime);

    void draw(sf::RenderWindow& window);

};

#endif
