#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "GameTile.h"
#include "PathTile.h"
#include "TreeTile.h"
#include "Entity.h"
#include "Monster.h"
#include "Game.h"
#include "GameText.h"
#include <iostream>
#include <vector>
#include <queue>
#include <cmath> // For abs()

using namespace sf;
using namespace std;
using sf::Vector2i;

//FUNCTION FOR ORDERING ARRAY
vector<Vector2i> reorderPath(Vector2i startPoint, Vector2i endPoint, vector<Vector2i> path, float windowHeight, float windowWidth) {
    vector<Vector2i> orderedPath;
    vector<Vector2i> unvisited = path;

    orderedPath.push_back(endPoint);

    vector<Vector2i> directions;
    if (endPoint.y == (windowHeight-50)/50){
        directions = {{0, -1}, {1, 0}, {-1, 0}, {0, 1}};
    } else if (endPoint.y == 0){
        directions = {{0, 1}, {-1, 0}, {1, 0}, {0, -1}};
    } else if (endPoint.x == 0){
        directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    } else if (endPoint.x == (windowWidth-50)/50){
        directions = {{-1, 0}, {0, 1} ,{0, -1}, {1, 0}}; // problem because if u go up it checks down frst but if you go down it checks up first... go straight up or down off the wall
    }
    while (!unvisited.empty()) {
        Vector2i current = orderedPath.back();
        bool foundNext = false;

        // Check distance to next points to avoid looping back
        for (auto dir : directions) {
            Vector2i neighbor(current.x + dir.x, current.y + dir.y);

            for (auto it = unvisited.begin(); it != unvisited.end(); ++it) {
                if (neighbor == *it) {
                    orderedPath.push_back(neighbor);
                    unvisited.erase(it);
                    foundNext = true;
                    break;
                }
            }
            if (foundNext) break;
        }
        if (!foundNext) {
            break; // No more tiles to process
        } // If no valid next step, break the loop
    }
    return orderedPath;
}

//START MAIN
int main() {
    /*

    Game game;
    game.Run();


    return 0;
    */

    //SETTING game DIMENSIONS
    float windowWidth;
    float windowHeight;
    cout << "Enter a game width(# of tiles):\n";
    cin >> windowWidth;
    cout << "Enter a game height(# of tiles):\n";
    cin >> windowHeight;
    windowWidth *= 50;
    windowHeight *= 50;
    RenderWindow window(VideoMode(windowWidth, windowHeight), "SFML-gameMap!", Style::Default);
    window.setFramerateLimit(60);


    //PATH
    bool loop = true;
    bool firstClick = true;
    bool endClick = true;
    bool startClick = true;
    vector<Vector2i> path;
    Vector2i newTile;
    Vector2i startPoint;
    Vector2i endPoint;
    Vector2i lastPoint;

    //DISPLAY "Editor Mode" FOR EDITOR MODE
    bool blinking;
    Text editorModeText;
    Font font;
    editorText(editorModeText, font, windowWidth, windowHeight);

    //CLOCK FOR E-PRESS DELAY AND BLINKING "Editor Mode" AND WALLS
    Clock clock;
    Clock clock2;
    Clock clock3;
    float keyCooldown = 0.4f;  // Half a second cooldown
    float elapsedTime = 0.0f;

    //CREATE game WORLD OBJECT
    Game game = Game(windowWidth/50, windowHeight/50);

    //STARTING LOOP
    while (window.isOpen()){

        Time deltaTime = clock3.restart();  // This returns the time elapsed since last restart

        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed)
                window.close();
        }

        //CHECKS IF E WAS PRESSED AND TURNS ON EDITOR MODE
        game.toggleEditorMode(elapsedTime, clock, keyCooldown);

        //IF IN EDITOR MODE THIS ALLOWS TILES TO BE PLACED
        if (game.isEditorMode == true && Mouse::isButtonPressed(Mouse::Left)) {
            Vector2i mousePos = Mouse::getPosition(window);
            int col = mousePos.x/50;
            int row = mousePos.y/50;

            //BORDER CONTROL FOR THE game
            if(0 <= mousePos.x && 0 <= mousePos.y && mousePos.x < windowWidth && mousePos.y < windowHeight){
                //PATH MAKING
                //ADDING START POINT
                game.addStartPoint(game, windowWidth, windowHeight, path, startPoint, col, row, firstClick, startClick, loop);

                //ADDING INTERMEDIATE PATH TILES
                game.addIntermediatePoints(game, path, newTile, col, row, firstClick, endClick);

                //ADDING END POINT
                game.addEndPoint(game, windowWidth, windowHeight, path, col, row, firstClick, endClick, startPoint, endPoint);
            }
        }

        // Toggle text visibility every `blinkInterval` seconds
        elapsedTime += clock2.restart().asSeconds();
        if (elapsedTime >= 1) {
            elapsedTime = 0.0f;  // Reset the timer
            blinking = !blinking;  // Toggle visibility
        }


        //CLEARS WINDOW
        window.clear();

        
        //START DRAWING
        //BASE TILES FOR game START
        for(int i = 0; i < game.gridHeight; i++){
            for(int j = 0; j < game.gridWidth; j++){
                window.draw(game.tiles[i][j]->sprite);
            }
        }

        //RANDOMLY GENERATED TREES/OBSTACLES
        for(int i = 0; i < game.gridHeight; i++){
            for(int j = 0; j < game.gridWidth; j++){
                if (game.stumps[i][j] != nullptr) {
                    window.draw(game.stumps[i][j]->sprite);  // Draw the tree if it's not null
                }
                if (game.bushes[i][j] != nullptr) {
                    window.draw(game.bushes[i][j]->sprite);  // Draw the tree if it's not null
                }
                if (game.trees[i][j] != nullptr) {
                    window.draw(game.trees[i][j]->sprite);  // Draw the tree if it's not null
                }
            }
        }
        
        //GETS ORDERED PATH
        vector<Vector2i> orderedPath = reorderPath(startPoint, endPoint, path, windowHeight, windowWidth);
        
        //DISPLAYING PATH LINE AND BLOCKS
        if(game.isEditorMode){
            game.drawPath(path, startPoint, endPoint, orderedPath, editorModeText, window, blinking);
        }

        //GREEN BORDER FOR SELECTING START
        if(firstClick){
            if(blinking){
                RectangleShape marker2(sf::Vector2f(50, 50));  // Size of each square
                marker2.setFillColor(Color::Green);
                for(int i = 0; i < windowWidth/50; i++){
                    marker2.setPosition(i*50, 0); //TOP
                    window.draw(marker2);
                    marker2.setPosition(0, i*50); //LEFT
                    window.draw(marker2);
                    marker2.setPosition(windowWidth-50, i*50); //RIGHT
                    window.draw(marker2);
                    marker2.setPosition(i*50, windowHeight-50); //BOTTOM
                    window.draw(marker2);
                }
            }
        } // RED BORDER FOR SELECTING END
        else if (endClick){
            if(blinking){
                RectangleShape marker3(sf::Vector2f(50, 50));  // Size of each square
                marker3.setFillColor(Color::Red);
                for(int i = 0; i < windowWidth/50; i++){
                    if(!(startPoint.x == i && startPoint.y == 0)){
                        marker3.setPosition(i*50, 0); //TOP
                        window.draw(marker3);
                    }
                    if(!(startPoint.x == 0 && startPoint.y == i)){
                    marker3.setPosition(0, i*50); //LEFT
                    window.draw(marker3);
                    }
                    if(!(startPoint.x == (windowWidth-50)/50 && startPoint.y == i)){
                    marker3.setPosition(windowWidth-50, i*50); //RIGHT
                    window.draw(marker3);
                    }
                    if(!(startPoint.x == i && startPoint.y == (windowHeight-50)/50)){
                    marker3.setPosition(i*50, windowHeight-50); //BOTTOM
                    window.draw(marker3);
                    }
                }
            }
        }




        //STARTS CREATING MONSTERS AND FOLLOWS PATH ONCE EDITOR IS CLOSED
        if(!game.isEditorMode){
            if (!orderedPath.empty()) {
                game.setUpEnemyPositions(orderedPath); // Reset each monster's position and currentTarget to restart the path
            } else {
                std::cout << "Path is empty, cannot set position!" << std::endl;
            }
            if (!game.monsters.empty()) {
                //game.monsters[0].pos = startPoint;

                float deltaTimeSeconds = deltaTime.asSeconds();
                game.monsters[0]->moveToNextPoint(deltaTimeSeconds);
                //cout << game.monsters[0]->path.size(); //!!!!!!!!!!!
                window.draw(game.monsters[0]->sprite);
            } else {
                std::cout << "Monster is nullptr!" << std::endl;
            }
        }
        
        window.display();

        //game.startMenu(window, windowWidth, windowHeight);

    }
}
