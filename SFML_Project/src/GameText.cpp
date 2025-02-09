#include "GameText.h"
#include <iostream>
using namespace sf;
using namespace std;


void editorText(Text& editorModeText, Font& font, float windowWidth, float windowHeight){
    if (!font.loadFromFile("TextFiles/PressStart2P.ttf")) {
        std::cout << "Error loading font!" << std::endl;
    }
    editorModeText.setFont(font);
    editorModeText.setString("Editor Mode");
    editorModeText.setCharacterSize(15);
    editorModeText.setFillColor(Color::Red);  // Set text color to white
    FloatRect textBounds = editorModeText.getLocalBounds();
    editorModeText.setPosition(
        (windowWidth - textBounds.width) / 2,  // Center horizontally
        (windowHeight - textBounds.height) / 6 // Center vertically);
    );
};