#include <SFML/Graphics.hpp>
#include "GameTile.h"
#include "PathTile.h"
#include "TowerTile.h"
#include "TreeTile.h"
#include "StumpTile.h"
#include "BushTile.h"
#include "Monster.h"
#include <vector>

#pragma once
using namespace sf;
using namespace std;

#ifndef GAME_H
#define GAME_H


class Game {
    public:
    
    void setUpInitialState(int x, int y);
    void setUpTiles(int x, int y);
    void generateRandomTrees();
    void setUpEnemyPositions(vector<Vector2i>);
    void toggleEditorMode(float& elapsedTime, Clock& clock, float keyCooldown);
    void generateRandomObstacles();
    void startMenu(RenderWindow& window, float x, float y);
    void addStartPoint(Game& Game, float windowWidth, float windowHeight, vector<Vector2i>& path, Vector2i& startPoint, int col, int row, bool& firstClck, bool& strtClck, bool& lp);
    void addIntermediatePoints(Game& Game, vector<Vector2i>& path, Vector2i newTile, int col, int row, bool& firstClck, bool& endClck);
    void addEndPoint(Game &Game, float windowWidth, float windowHeight, vector<Vector2i>& path, int col, int row, bool& firstClick, bool& endClick, Vector2i& startPoint, Vector2i& endPoint);
    void drawPath(vector<Vector2i>& path, Vector2i& startPoint, Vector2i& endPoint, vector<Vector2i>& orderedPath, Text& editorModeText, RenderWindow& window, bool& blinking);
    bool isEditorMode;
    Vector2i exitPos;
    Vector2i playerPos;
    vector<Vector2i> enemyPositions;
    vector<Monster*> monsters;
    vector<vector<GameTile*>> tiles;
    vector<vector<TreeTile*>> trees;
    vector<vector<BushTile*>> bushes;
    vector<vector<StumpTile*>> stumps;
    int gridHeight;
    int gridWidth;
    vector<Vector2i> path;
    void draw(sf::RenderWindow& window);
    Game(float x, float y);
};

#endif