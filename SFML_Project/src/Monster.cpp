#include "Monster.h"
#include <iostream>
#include <cmath> // For abs()

using namespace sf;
using namespace std;

Monster::Monster(Vector2f pos, vector<sf::Vector2i>& path) 
    : Entity(MONSTER_TEXTURE, pos, {0.06f, 0.06f}) {

    if (!path.empty()) {
        this->path = path;
        //pos = Vector2f(startPoint.x, startPoint.y);  // Set to the first pos in the path
    }

    bobbingAmplitude = 50.0f;  // How much the character bobs
    bobbingSpeed = 50.0f;  // Speed of the bobbing
    bobbingOffset = 0.0f;  // Start position of bobbing

    animationFrameTime = 0.2f;  // Time between frames
    lastFrameTime = 0.0f;  // Keeps track of time for frame switching
    currentFrame = 0;  // 0 for first frame, 1 for second frame

}

bool isTrue = true;
void Monster::moveToNextPoint(float deltaTime) {
    if(isTrue){
        currentTarget = path.size()-1;
        isTrue = false;
    }

    if (currentTarget >= 0) {  // Allow reaching the last point
        Vector2i target = path[currentTarget];  // Target the current point
        cout << "\nPath Length is: " << path.size() << "\n";
        cout << "\nGoing to " << path[currentTarget].x << "x and " << path[currentTarget].y << "y\n";
        cout << pos.x << " < "<<target.x;
        if (pos.x/50 < target.x) {
            pos.x += speed;
            sprite.setPosition(pos);
        }
        else if (pos.x/50 > target.x){
            pos.x -= speed;
            sprite.setPosition(pos);
        }
        if (pos.y/50 < target.y) {
            pos.y += speed;
            sprite.setPosition(pos);
        }
        else if (pos.y/50 > target.y) {
            pos.y -= speed;
            sprite.setPosition(pos);
        }

        if (pos.x/50 == target.x && pos.y/50 == target.y && currentTarget != 0) {
            currentTarget--;  // Move to the next point when the current one is reached
        }


        // Update bobbing position (simple sine wave for bobbing effect)
        //bobbingOffset = sin(deltaTime * bobbingSpeed) * bobbingAmplitude;
        //float bobbedYPosition = pos.y + bobbingOffset;
        //cout << "\n" << bobbedYPosition << "HI\n";
        // Update animation frame
        lastFrameTime += deltaTime;
        if (lastFrameTime >= animationFrameTime) {
            lastFrameTime = 0.0f;
            currentFrame = (currentFrame + 1) % 2;  // Toggle between 0 and 1 for two frames
            string texture = (currentFrame == 0) ? "images/frame-2.png" : "images/frame-1.png";  // Toggle textures
            setUpSprite(texture, {0.06f, 0.06f});  // Update sprite texture
        }

        //sprite.setPosition(pos.x, bobbedYPosition);  // Update sprite position

    }
}

void Monster::draw(sf::RenderWindow& window) {
    //sprite.setPosition(pos);  // Set the sprite position to the current monster position
    window.draw(sprite);  // Draw the monster sprite
}
