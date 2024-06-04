#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string.h>

enum Colors
{
    Cyan,
    Blue,
    Green,
    Red,
    Yellow,
    Orange,
};

enum ToolBarWord
{
    SCORE,
    AVAILABLE,
    LEFT,
    TAKE,
    TIME 
};

enum Textures
{
    X_texture,
    Background,
    Back,
    Label,
    GameBackground,
    YouWin,
    YouLose
};

enum Button
{
    Play,
    Continue,
    Exit,
};

//window
const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 1400;

//stick
const int ROW = 15; 
const int COL = 10; 
const int RADIUS = 10;
const int OUTLINE = 3;
const int LENGTH = 60;

const int WIDTH = 5;
const float STICK_WIDTH = WIDTH + (2 * OUTLINE);
const float STICK_LENGTH = LENGTH + (2 * OUTLINE);
const float HEX_WIDTH = RADIUS * std::sqrt(3.f) + (2*OUTLINE);
const int TOOL_BAR = 5;

//enums
const int TEXTURES = 7;
const int BUTTONS = 3;

//backgraound
const sf::Color WINDOW_COLOR = sf::Color::Black;


class Resources
{
public:
    Resources();
    const sf::Texture& getTexture(const Textures)const;
    const sf::Texture& getButton(const Button)const;
    const sf::Color* getColorArray()const;
    const sf::Font& getFont()const;
    static Resources& instance();

private:
    sf::Color m_colorArray[6] = { sf::Color::Cyan, sf::Color::Blue, sf::Color::Green,
        sf::Color::Red, sf::Color::Yellow, sf::Color::Color(255, 119, 0) };
    sf::Texture m_textures[TEXTURES];
    sf::Texture m_Buttons[BUTTONS];
    sf::Font m_font;

    void LoadFromFile();

};