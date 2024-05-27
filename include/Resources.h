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

enum Score
{
    Player,
    Computer,
};

//window
const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 1400;

//stick
const int ROW = 26; //גובה 
const int COL = 50; //רוחב
const int RADIUS = 80;
const int OUTLINE = 3;
const int LENGTH = 60;

const int WIDTH = 5;
const float STICK_WIDTH = WIDTH + (2 * OUTLINE);
const float STICK_LENGTH = LENGTH + (2 * OUTLINE);

//const float HEX_WIDTH = RADIUS * std::sqrt(3.f) + (2*OUTLINE);
//const float HEX_HEIGHT = 2.f * RADIUS + (2 * OUTLINE);
//const float HEX_EDGH = 2 * RADIUS * sin(3.14159 / 3);
//const int LENGTH = 30;
//const int WIDTH = 5;
//const int OUTLINE = 1;
//const float STICK_WIDTH = WIDTH + (2 * OUTLINE);
//const float STICK_LENGTH = LENGTH + (2 * OUTLINE);


//grid
const float GRID_WIDTH = STICK_WIDTH * COL;
const float GRID_HEGHT = ROW * (STICK_LENGTH * 3.f / 4.f);

//enums
const int TEXTURES = 7;
const int BUTTONS = 3;

//const locations
const int PLAYER_INDEX = ROW * COL - COL;
const int COMPUTER_INDEX = COL - 1;

//backgraound
const sf::Color WINDOW_COLOR = sf::Color::Black;


class Resources
{
public:
    Resources();
    ~Resources() = default;
    static Resources& instance();

    const sf::Color* getColorArray()const;
    const sf::Texture& getTexture(const Textures)const;
    const sf::Texture& getButton(const Button)const;
    const sf::Font& getFont()const;


private:
    sf::Color m_colorArray[6] = { sf::Color::Cyan, sf::Color::Blue, sf::Color::Green,
        sf::Color::Red, sf::Color::Yellow, sf::Color::Color(255, 119, 0) };

    sf::Texture m_textures[TEXTURES];
    sf::Texture m_Buttons[BUTTONS];

    sf::Font m_font;

    void LoadFromFile();

};