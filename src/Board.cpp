#pragma once

#include "Board.h"
#include <iostream>
#include <iterator>



Board::Board()
{
	createRectangles();
	createGridFrame();
	//locateObjects();
	std::random_device rd; // î÷åø ìîñôøéí øðãåîìééí
	std::mt19937 gen(rd()); // îçåìì îñôøéí øðãåîìééí îîùôçú mersenne_twister_engine
	std::uniform_int_distribution<int> dis(20, 30); // ôéæåø àçéã ùì îñôøéí áéï 30 ìÎ50
	m_numOfStick = dis(gen); // äùîä ùì îñôø øðãåîìé ìÎm_numOfStic

}

void Board::createRectangles()
{
	for (int rectangle = 0; rectangle < 6; ++rectangle)
	{
		m_rectangles.push_back(createRectangle(rectangle));
	}
}

void Board::createFile(std::ofstream& m_ofile)
{
	//m_ofile.open("Board.txt"); // פתיחת הקובץ לכתיבה

	//if (!m_ofile.is_open())
	//{
	//	std::cout << "Error: Unable to open file for writing.\n";
	//	return;
	//}

	try
	{
		std::string inputFileName = "Board.txt";
		std::string expectedExtension = ".txt";
		validateFile(inputFileName, expectedExtension);

		std::ofstream m_ofile;
		m_ofile.open("Board.txt"); // פתיחת הקובץ לכתיבה

		if (!m_ofile.is_open()) 
		{
			std::cout << "Error: Unable to open file for writing.\n";
		}
		// כתיבת מידע על כל סטיק לקובץ
		for (const auto& stick : m_stick)
		{
			m_ofile << stick->getLocation().x << stick->getLocation().y << "\n";
			m_ofile << stick->getColor().r << stick->getColor().g << stick->getColor().b << "\n";
			m_ofile << stick->getIndex() << "\n";
		}

		m_ofile.close(); // סגירת הקובץ
	}

	catch (const std::exception& e)
	{
		std::cerr << "File validation error: " << e.what() << std::endl;
	}
}


void Board::validateFile(const std::string & fileName, const std::string & expectedExtension) 
{
	// Check if file exists
	std::ifstream file(fileName);
	if (!file.is_open()) {
		throw std::runtime_error("File not found: " + fileName);
	}

	// Check file extension
	if (fileName.substr(fileName.find_last_of('.')) != expectedExtension) {
		throw std::runtime_error("File extension mismatch: expected " + expectedExtension);
	}

	// Read and validate file content
	std::string line;
	while (std::getline(file, line)) {
		for (char c : line) {
			if (!std::isdigit(c) && !std::isspace(c)) {
				throw std::runtime_error("Invalid content in file: non-digit character found: " + line);
			}
		}
	}

	std::cout << "File validation successful." << std::endl;
}



const sf::RectangleShape Board::createRectangle(const int index) const
{
	sf::RectangleShape rec;

	//Position
	rec.setSize(sf::Vector2f(50.f, 50.f));
	rec.setPosition(WINDOW_WIDTH * 0.5 - 300 + index * 100, WINDOW_HEIGHT * 0.9);

	//Style
	rec.setOutlineThickness(2.f);
	rec.setFillColor(Resources::instance().getColorArray()[index]);

	return rec;
}

void Board::findStick(const sf::Vector2f location)
{
	for (auto it = m_stick.rbegin(); it != m_stick.rend(); ++it)
	{
		if ((*it)->isLocationInside(location))
		{
			auto regular_it = (it + 1).base();
			if ((*regular_it)->isEraseable())
			{
				m_sitckTakeCounter++;
				m_stick.erase(regular_it);
				break;
			}
		}
	}
}

void Board::fillAvailableStick()
{
	// Assuming the number of sticks is the size of m_sticks vector
	int numOfSticks = static_cast<int>(m_stick.size());
	for (auto& stick : m_stick)
	{
		stick->checkAvailableStick(m_stick, numOfSticks);
	}
}


void Board::createBoard()
{
	for (int row = 0; row < m_numOfStick; ++row)
	{
		auto temp = std::make_shared<Stick>(row, 6);
		for (const auto& stick1 : m_stick)
		{
			if (Stick::isOverlaped(temp->getrec(), stick1->getrec()))
			{
				temp.get()->addOverLapped(stick1);
				stick1.get()->addOverLapped(temp);
			}
		}
		m_stick.push_back(temp);
	}


	/*if (m_stick[m_col - 1].getColor() == m_stick[m_row * m_col - m_col].getColor())
	{
		m_stick[COMPUTER_INDEX].get().setFillColor(Resources::instance().getColorArray()[Cyan]);
		m_stick[PLAYER_INDEX].get().setFillColor(Resources::instance().getColorArray()[Blue]);
	}*/
}

void Board::init()
{
	m_stick.clear();
	//m_graph.clear();
	createBoard();
	//connectNeighbors();
}

//àéê ìöééø àú úçéìú äîùç÷ . ìôé îä ?
void Board::drawBoard(sf::RenderWindow& window)
{
	//window.clear();
	window.clear(sf::Color::Color(210, 210, 210));
	for (int stick = 0; stick < m_stick.size(); stick++)
	{
		window.draw(m_stick[stick]->getrec());
	}
	for (int rectangle = 0; rectangle < 4; rectangle++)
	{
		window.draw(m_grid_frame[rectangle]);
	}

	//window.draw(m_back);
}

void Board::createGridFrame()
{
	// Define the thickness of the border
	//const float borderThickness = 8.0f;

	//// up
	//m_grid_frame[0].setSize(sf::Vector2f(GRID_WIDTH , borderThickness));
	//m_grid_frame[0].setFillColor(sf::Color::Black);
	//m_grid_frame[0].setPosition(sf::Vector2f(((WINDOW_WIDTH / 2) - (GRID_WIDTH / 2) - RADIUS),
	//	(WINDOW_HEIGHT / 2) - (GRID_HEGHT / 2) - RADIUS - borderThickness));

	//// down
	//m_grid_frame[1].setSize(sf::Vector2f(GRID_WIDTH, borderThickness));
	//m_grid_frame[1].setFillColor(sf::Color::Black);
	//m_grid_frame[1].setPosition(sf::Vector2f((WINDOW_WIDTH / 2) - (GRID_WIDTH / 2) - RADIUS,
	//	(WINDOW_HEIGHT / 2) + (GRID_HEGHT / 2) - RADIUS));

	//// right
	//m_grid_frame[2].setSize(sf::Vector2f(borderThickness, GRID_HEGHT + RADIUS));
	//m_grid_frame[2].setFillColor(sf::Color::Black);
	//m_grid_frame[2].setPosition(sf::Vector2f((WINDOW_WIDTH / 2) + (GRID_WIDTH / 2) - RADIUS - borderThickness,
	//	(WINDOW_HEIGHT / 2) - (GRID_HEGHT / 2) - RADIUS));

	//// left
	//m_grid_frame[3].setSize(sf::Vector2f(borderThickness, GRID_HEGHT + RADIUS));
	//m_grid_frame[3].setFillColor(sf::Color::Black);
	//m_grid_frame[3].setPosition(sf::Vector2f((WINDOW_WIDTH / 2) - (GRID_WIDTH / 2) - RADIUS,
	//	(WINDOW_HEIGHT / 2) - (GRID_HEGHT / 2) - RADIUS));
}

int Board::returnSticksAva() const
{
	return m_numOfStick; 
}

int Board::returnSticksLeft()const
{
	return m_numOfStick - m_sitckTakeCounter;
}

int Board::returnSticksTake()const
{
	return m_sitckTakeCounter;
}
