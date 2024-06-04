#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <Resources.h>
#include "Stick.h"
#include <random>
#include <iostream>
#include <fstream>


class Board
{
public:
	Board();
	void findStick(const sf::Vector2f);
	void drawBoard(sf::RenderWindow&);
	void createFile(std::ofstream& m_ofile);
	void init();
	//void fillAvailableStick();
	void fillAvailableSticks();
	void printAvailableSticksByColor() const;
	void hintPressed(sf::RenderWindow& m_window);
	//void checkAvailableStick(const std::vector<std::shared_ptr<Stick>>& sticks, int numOfSticks);
	int returnSticksAva() const;
	int returnSticksLeft()const;
	int returnSticksTake()const;
	

private:
	//Stick m_stickClass;
	int m_row;
	int m_col;
	int m_numOfStick;
	int m_sitckTakeCounter;
	int m_sitckAvailableCounter;

	sf::Clock m_clock;
	float m_blinkInterval = 0.5f;

	int counter = 0;
	std::vector<std::shared_ptr <Stick>> m_stick;
	sf::RectangleShape m_grid_frame[4];
	std::vector<sf::RectangleShape> m_rectangles;
	std::vector<std::shared_ptr <Stick>> m_available;
	std::vector<std::vector<std::shared_ptr<Stick>>> m_availableByColor;

	sf::Sprite m_backgroung;
    
	////functions
	void createBoard();
	void createGridFrame();
	void createRectangles();
	void validateFile(const std::string& fileName, const std::string& expectedExtension);
	const sf::RectangleShape createRectangle(const int) const;
	

};