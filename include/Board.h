#pragma once
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include <Resources.h>
#include <iostream>
#include <fstream>
#include <random>
#include "Stick.h"


class Board
{
public:
	Board();
	void hintPressed(sf::RenderWindow& m_window);
	void drawBoard(sf::RenderWindow&);
	void createFile(std::ofstream& m_ofile);
	void findStick(const sf::Vector2f);
	void printAvailableSticksByColor() const;
	void fillAvailableSticks();
	void init();
	int returnSticksLeft()const;
	int returnSticksTake()const;
	int returnSticksAva() const;
	int returnScore() const;
	
private:
	int m_sitckAvailableCounter = 0;
	int m_sitckTakeCounter = 0;
	int m_scoureCounter = 0;
	int m_numOfStick;
	int m_row;
	int m_col;

	sf::Clock m_clock;
	float m_blinkInterval = 0.5f;
	
	sf::RectangleShape m_grid_frame[4];
	std::vector<sf::RectangleShape> m_rectangles;
	std::vector<std::shared_ptr <Stick>> m_stick;
	std::vector<std::shared_ptr <Stick>> m_available;
	std::vector<std::vector<std::shared_ptr<Stick>>> m_availableByColor;

	sf::Sprite m_backgroung;
    
	////functions
	void createBoard();
	void validateFile(const std::string& fileName, const std::string& expectedExtension);
	const sf::RectangleShape createRectangle(const int) const;

};