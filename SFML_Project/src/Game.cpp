#include "Game.h"

#include <iostream>
#include <random>

using namespace sf;
using namespace std;

Game::Game(float x, float y)
    : gridHeight(y)
    , gridWidth(x)
    , isEditorMode(true)
{
    setUpInitialState(x,y);
}

void Game::toggleEditorMode(float& elapsedTime, Clock& clock, float keyCooldown) {
    if(Keyboard::isKeyPressed(Keyboard::E) && elapsedTime >= keyCooldown) {
        isEditorMode = !isEditorMode;
        cout << (isEditorMode ? "Editor Mode ON" : "Play Mode ON") << endl;
        elapsedTime = 0.0f;
    }
    elapsedTime += clock.restart().asSeconds();
}


void Game::setUpInitialState(int x, int y){
    exitPos = Vector2i(1,0);
    playerPos = Vector2i(gridHeight-1, gridHeight-1);
    //setUpEnemyPositions();
    setUpTiles(x, y);
    generateRandomObstacles();

}

void Game::draw(sf::RenderWindow& window) {
    // Draw all monsters
    for (auto& monster : monsters) {
        monster->draw(window);  // Calling the draw method for each monster
    }
}


void Game::drawPath(vector<Vector2i>& path, Vector2i& startPoint, Vector2i& endPoint, vector<Vector2i>& orderedPath, Text& editorModeText, RenderWindow& window, bool& blinking){
    for (size_t i = 0; i < path.size(); i++) {
        sf::RectangleShape marker(sf::Vector2f(50, 50));  // Size of each square
        marker.setPosition(path[i].x * 50, path[i].y * 50);  // Position based on path coordinates

        if (path[i].x == startPoint.x && path[i].y == startPoint.y) {
            marker.setFillColor(Color::Green);  // Start point (Green)
            //endPoint.x == path[i].x  && endPoint.x == path[i].y * 50
        } else if (path[i].x == endPoint.x && path[i].y == endPoint.y) {
            marker.setFillColor(Color::Red);    // End point (Red)
        } else {
            marker.setFillColor(Color::Blue);   // Path points (Blue)
        }
        window.draw(marker);  // Draw the marker
    }

    // Draw the path
    if (!orderedPath.empty()) {
        for (size_t i = 0; i < orderedPath.size() - 1; i++) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(orderedPath[i].x * 50 + 25, orderedPath[i].y * 50 + 25)),
                sf::Vertex(sf::Vector2f(orderedPath[i + 1].x * 50 + 25, orderedPath[i + 1].y * 50 + 25))
            };
        window.draw(line, 2, sf::Lines);
        }
    }
    if(blinking){
        window.draw(editorModeText);
    }
}


void Game::setUpEnemyPositions(vector<Vector2i> vec){
    enemyPositions.clear();
    if (!vec.empty()) {
        enemyPositions.push_back(vec[vec.size()-1]);
        //enemyPositions.push_back(vec[vec.size()-1]);
        //enemyPositions.push_back(vec[vec.size()-1]);
        path = vec;
        for (auto& pos : enemyPositions) {

            std::random_device rd;  // Obtain a random seed from the hardware
            std::mt19937 gen(rd()); // Mersenne Twister engine

            // Define the distribution within the range [min, max]
            std::uniform_int_distribution<> dist(0, 5);

            // Generate the random integer
            int random_num_x = dist(gen);
            int random_num_y = dist(gen);


            monsters.push_back(new Monster({(pos.x * 50), (pos.y * 50)}, path));
            //cout << "\nMonster created"; // Spawn monsters at enemy positions
        }
    } else {
        cout << "Invalid path!" << std::endl;
    }
}


void Game::generateRandomObstacles() {
    srand(time(0));  // Initialize the random seed
    trees.clear();  // Clear any existing trees
    bushes.clear(); // Clear any existing bushes
    stumps.clear(); // Clear any existing stumps
    // Loop through the tower tiles and randomly decide to place a tree
    for (int i = 0; i < gridHeight; i++) {
        vector<TreeTile *> treeRow;
        vector<RockTile *> bushRow;
        vector<StumpTile *> stumpRow;

        for (int j = 0; j < gridWidth; j++) {
            // Place a tree on the tile with a 20% chance
            if (rand() % 10 == 0) {  // Adjust the 5 for more or fewer trees
                treeRow.push_back(new TreeTile({j * 50, i * 50}));
            }else {
                treeRow.push_back(nullptr);  // No tree at this position
            }
            if (rand() % 30 == 0) {  // Adjust the 5 for more or fewer trees
                bushRow.push_back(new RockTile({j * 50, i * 50}));
            }else {
                bushRow.push_back(nullptr);  // No tree at this position
            }
            if (rand() % 20 == 0) {  // Adjust the 5 for more or fewer trees
                stumpRow.push_back(new StumpTile({j * 50, i * 50}));
            }else {
                stumpRow.push_back(nullptr);  // No tree at this position
            }
        }
        trees.push_back(treeRow);
        bushes.push_back(bushRow);
        stumps.push_back(stumpRow);
    }
}


void Game::startMenu(RenderWindow& window, float x, float y){
    
    Font font;
        if (!font.loadFromFile("arial.ttf")) {
            cerr << "Error loading font!" << endl;
            return;
        }

        RectangleShape buttons[3];
        Text buttonTexts[3];
        string labels[3] = {"Start", "Rules", "Exit"};

        for (int i = 0; i < 3; ++i) {
            buttons[i].setSize(Vector2f(200, 50));
            buttons[i].setFillColor(Color::Blue);
            buttons[i].setPosition((x - 200) / 2, 200 + i * 80);

            buttonTexts[i].setFont(font);
            buttonTexts[i].setString(labels[i]);
            buttonTexts[i].setCharacterSize(24);
            buttonTexts[i].setFillColor(Color::White);
            buttonTexts[i].setPosition((x - 100) / 2, 210 + i * 80);
        }

        while (window.isOpen()) {
            Event event;
            Vector2f mousePos = (Vector2f)Mouse::getPosition(window);

            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();

                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                    for (int i = 0; i < 3; ++i) {
                        if (buttons[i].getGlobalBounds().contains(mousePos)) {
                            if (labels[i] == "Exit") {
                                window.close();
                            } else {
                                cout << labels[i] << " button clicked!" << endl;
                            }
                        }
                    }
                }
            }

            for (int i = 0; i < 3; ++i) {
                if (buttons[i].getGlobalBounds().contains(mousePos)) {
                    buttons[i].setFillColor(Color::Green);
                } else {
                    buttons[i].setFillColor(Color::Blue);
                }
            }

            window.clear();
            for (int i = 0; i < 3; ++i) {
                window.draw(buttons[i]);
                window.draw(buttonTexts[i]);
            }
            window.display();
        }
    
}

void Game::setUpTiles(int x, int y){
    tiles.clear();
    for(int i = 0; i < x; i++){
        vector<GameTile*> generateMap;
        for(int j = 0; j < y; j++){
            generateMap.push_back(new TowerTile({j*50,i*50}));
        }
        tiles.push_back(generateMap);
    }
}

void Game::addStartPoint(Game& Game, float windowWidth, float windowHeight, vector<Vector2i>& path, Vector2i& startPoint, int col, int row, bool& firstClck, bool& strtClck, bool& lp) {
    if(firstClck && strtClck && (0 == col || 0 == row || (windowHeight-50)/50 == row || (windowWidth-50)/50 == col)){
        startPoint = Vector2i(col, row);  // Start point was set successfully.
        path.push_back(startPoint);
        firstClck = false;
        strtClck = false;
        cout << "\nStart point was set successfully.\n";
        cout << "X: " << path[path.size()-1].x << " and Y: " << path[path.size()-1].y << "\n";
        lp = false;

        //DELETING TILES AND PLACING PATHS
        if (Game.trees[row][col] != nullptr) {
            delete Game.trees[row][col];  // Free memory
            Game.trees[row][col] = nullptr;  // Set the pointer to nullptr
        }
        if (Game.stumps[row][col] != nullptr) {
            delete Game.stumps[row][col];  // Free memory
            Game.stumps[row][col] = nullptr;  // Set the pointer to nullptr
        }
        if (Game.bushes[row][col] != nullptr) {
            delete Game.bushes[row][col];  // Free memory
            Game.bushes[row][col] = nullptr;  // Set the pointer to nullptr
        }
        if (Game.tiles[row][col] != nullptr) {
            delete Game.tiles[row][col];  // Free memory
        }
        Game.tiles[row][col] = new PathTile({col * 50, row * 50});
    }
}

void Game::addIntermediatePoints(Game& Game, vector<Vector2i>& path, Vector2i newTile, int col, int row, bool& firstClck, bool& endClck){
    if ((!endClck) &&
    (!firstClck) &&
    (((abs(col - path.back().x) == 1 && row == path.back().y)) ||
    ((abs(row - path.back().y) == 1 && col == path.back().x))) &&
    !(col == path.back().x && row == path.back().y)) {

    // Check if the tile is already in the path
    Vector2i newTile(col, row);
    bool alreadyInPath = false;
    for (auto& tile : path) {
        if (tile == newTile) {
            alreadyInPath = true;
            break;
        }
    }

    // If it's not in the path, add it to the path
    if (!alreadyInPath) {
        path.push_back(newTile);  // Connecting points

        // Optionally, delete any old tile and place a new pathTile (already in your code)
        delete Game.tiles[row][col];  // Free memory
        if (Game.trees[row][col] != nullptr) {
            delete Game.trees[row][col];  // Free memory
            Game.trees[row][col] = nullptr;  // Set the pointer to nullptr
        }
        if (Game.stumps[row][col] != nullptr) {
            delete Game.stumps[row][col];  // Free memory
            Game.stumps[row][col] = nullptr;  // Set the pointer to nullptr
        }
        if (Game.bushes[row][col] != nullptr) {
            delete Game.bushes[row][col];  // Free memory
            Game.bushes[row][col] = nullptr;  // Set the pointer to nullptr
        }
        Game.tiles[row][col] = new PathTile({col * 50, row * 50});
    }
    }
}


void Game::addEndPoint(Game &Game, float windowWidth, float windowHeight, vector<Vector2i>& path, int col, int row, bool& firstClick, bool& endClick, Vector2i& startPoint, Vector2i& endPoint){
    if(!firstClick && endClick && !(col == startPoint.x && row == startPoint.y) && (0 == col || 0 == row || (windowHeight-50)/50 == row || (windowWidth-50)/50 == col)){
        endPoint = Vector2i(col, row);  // End point was set successfully.
        path.push_back(endPoint);
        cout << "\nEnd point was set successfully.\n";
        cout << "X: " << path[0].x << " and Y: " << path[0].y << "\n";
        endClick = !endClick;

        //DELETING TILES AND PLACING PATHS
        delete Game.tiles[row][col];  // Free memory
        if (Game.trees[row][col] != nullptr) {
            delete Game.trees[row][col];  // Free memory
            Game.trees[row][col] = nullptr;  // Set the pointer to nullptr
        }
        if (Game.stumps[row][col] != nullptr) {
            delete Game.stumps[row][col];  // Free memory
            Game.stumps[row][col] = nullptr;  // Set the pointer to nullptr
        }
        if (Game.bushes[row][col] != nullptr) {
            delete Game.bushes[row][col];  // Free memory
            Game.bushes[row][col] = nullptr;  // Set the pointer to nullptr
        }
        Game.tiles[row][col] = new PathTile({col * 50, row * 50});
    }
}
