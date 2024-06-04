#include "Board.h"


Board::Board()
{
	std::random_device rd; 
	std::mt19937 gen(rd());
	//Grill the number of sticks on the board
	std::uniform_int_distribution<int> dis(20, 25);
	//save the number of sticks
	m_numOfStick = dis(gen); 
}

//This function creates and opens an existing file for the game board. 
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

//This function checks the integrity of the file.
void Board::validateFile(const std::string & fileName, const std::string & expectedExtension) 
{
	// Check if file exists
	std::ifstream file(fileName);
	if (!file.is_open()) 
	{
		throw std::runtime_error("File not found: " + fileName);
	}

	// Check file extension
	if (fileName.substr(fileName.find_last_of('.')) != expectedExtension) 
	{
		throw std::runtime_error("File extension mismatch: expected " + expectedExtension);
	}

	// Read and validate file content
	std::string line;
	while (std::getline(file, line)) 
	{
		for (char c : line) 
		{
			if (!std::isdigit(c) && !std::isspace(c)) 
			{
				throw std::runtime_error("Invalid content in file: non-digit character found: " + line);
			}
		}
	}
	std::cout << "File validation successful." << std::endl;
}

//This function creates the rectangels on the board ??????????????????????????????
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

//This function finds the stick location on the board, we chack here if the 
//stick was pressed by the user.
void Board::findStick(const sf::Vector2f location)
{
	//loop to go over all the sticks in the stick vector
	for (auto it = m_stick.rbegin(); it != m_stick.rend(); ++it)
	{
		//Checking whether the stick is pressed by the user
		if ((*it)->isLocationInside(location))
		{
			auto regular_it = (it + 1).base();
			//chack if we can erase the stick from the board
			if ((*regular_it)->isEraseable())
			{
				m_sitckTakeCounter++;
				m_scoureCounter += (*regular_it)->getStickScore();
				//delete from the over lapped sticks the current stick
				(*regular_it)->deleteOverLapped();
				m_stick.erase(regular_it);
				break;
			}
		}
	}
}

//This function creates the vector of sticks that can currently 
//be picked up by the user from the board
void Board::fillAvailableSticks()
{
	// Clear the previous available sticks
	m_availableByColor.clear();
	m_availableByColor.resize(6); // Assuming 6 different colors
	//loop to go iver all the sticks on the board
	for (const auto& stick : m_stick)
	{
		//check if the stick can be picked up from the board. 
		if (stick->checkAvailableStick())
		{
			//add to the Available vector
			m_availableByColor[stick->getColorIndex()].push_back(stick);
		}
	}
	//find the size of all the Available sticks on the board.
	m_sitckAvailableCounter = 0;
	for (const auto& colorSticks : m_availableByColor)
	{
		m_sitckAvailableCounter += colorSticks.size();
	}

}

//This function marks the Available sticks on the board by the score = color. 
void Board::hintPressed(sf::RenderWindow& window)
{
	// a loop to go over the vector of the available sticks on the board
	for (size_t colorIndex = 0; colorIndex < m_availableByColor.size(); ++colorIndex)
	{
		for (const auto& stick : m_availableByColor[colorIndex])
		{
			// Change color of all sticks in the current color group to black
			stick->setColor(sf::Color::Black);
		}

		// Draw all elements here, including the updated sticks
		for (const auto& colorSticks : m_availableByColor)
		{
			for (const auto& stick : colorSticks)
			{
				window.draw(stick->getShape());
			}
		}
		window.display();

		sf::sleep(sf::seconds(0.5)); // Wait for 0.5 second

		for (const auto& stick : m_availableByColor[colorIndex])
		{
			// Reset color of all sticks in the current color group
			stick->resetColor();
		}

		// Draw all elements here, including the reset sticks
		for (const auto& colorSticks : m_availableByColor)
		{
			for (const auto& stick : colorSticks)
			{
				window.draw(stick->getShape());
			}
		}
		window.display();

		sf::sleep(sf::seconds(0.5f)); // Short delay before highlighting next color group
	}
}

//This function creates the sticks on the game board
void Board::createBoard()
{
	//this loop produce sticks as the number of sticks griled
	for (int row = 0; row < m_numOfStick; ++row)
	{
		auto temp = std::make_shared<Stick>(row, 6);
		//check if the stick we created is overlapped with other sticks
		for (const auto& stick1 : m_stick)
		{
			if (Stick::isOverlaped(temp->getrec(), stick1->getrec()))
			{
				//Adding to the vector of the stick we created
				temp.get()->addOverLapped(stick1);
				//Adding to the vector of the sticks with which the new stick collides
				stick1.get()->addOverLapped(temp);
			}
		}
		//Adding to the sticks vector
		m_stick.push_back(temp);
	}
}

//This function initialize  the game
void Board::init()
{
	m_stick.clear();
	createBoard();
}


//This function draws the board
void Board::drawBoard(sf::RenderWindow& window)
{
	//Delete everything that was in the window until now
	window.clear(sf::Color::Color(210, 210, 210));
	//Draw the sticks
	for (int stick = 0; stick < m_stick.size(); stick++)
	{
		window.draw(m_stick[stick]->getrec());
	}
	//Draw the franme of the buttons
	for (int rectangle = 0; rectangle < 4; rectangle++)
	{
		window.draw(m_grid_frame[rectangle]);
	}
}

//This function returns the number of Available sticks on the board
int Board::returnSticksAva() const
{
	return m_sitckAvailableCounter;
}

//This function returns the number of sticks left on the board
int Board::returnSticksLeft()const
{
	return m_numOfStick - m_sitckTakeCounter;
}

//This function returns the number of sticks take from the board
int Board::returnSticksTake()const
{
	return m_sitckTakeCounter;
}

//This function returns the score depending on the sticks collected
int Board::returnScore()const
{
	return m_scoureCounter;
}
