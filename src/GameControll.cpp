#include "GameControll.h"


GameControll::GameControll()
    :m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pick Up Sticks"), m_game_over(false)
{
    m_window.setFramerateLimit(60);
    m_YouWin.setTexture(Resources::instance().getTexture(YouWin));
    m_YouLose.setTexture(Resources::instance().getTexture(YouLose));    // locateObjects();
}

//This function is responsible for the course of the game
void GameControll::run()
{
    m_GameClock.restart();
    while (m_window.isOpen())
    {
        m_window.clear(sf::Color::Color(0, 0, 0));
        //draw the menu in the first window of the game
        m_menu.drawMenu(this->m_window);
        m_window.display();
        float deltaTime = m_GameClock.restart().asSeconds();
        //Waiting for the user's action in the first window of the game
        if (auto event = sf::Event{}; m_window.waitEvent(event))
        {
            switch (event.type)
            {
            //Closing the game window
            case sf::Event::Closed:
            {
                m_window.close();
                break;
            }
            //Clicking on the first game window
            case sf::Event::MouseButtonReleased:
            {
                auto location = m_window.mapPixelToCoords(
                    { event.mouseButton.x, event.mouseButton.y });
                handleMenuClick(location);
                break;
            }
            //Mouse move on the first game window
            case sf::Event::MouseMoved:
            {
                auto location = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
                handleMenuMouseMoved(location);
            }

            }

        }
        //Closing the game window
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            m_window.close();
        }
    }
}

//This function checks whether one of the buttons in menu has been pressed
void GameControll::handleMenuMouseMoved(const sf::Vector2f location)
{
    //loop to go over the buttons
    for (int button = Play; button <= Exit; button++)
    {
        //check if a button preesed
        if ((m_menu.getButton((Button)button).getGlobalBounds().contains(location)))
        {
            m_menu.ButtonPress((Button)button);
        }
        else
        {
            m_menu.ButtonRelease((Button)button);
        }
    }
}

//This function performs the action that is called after the user clicks one of the buttons in the menu
void GameControll::handleMenuClick(const sf::Vector2f location)
{
    //start the game
    if (m_menu.getButton(Play).getGlobalBounds().contains(location))
    {
        //rest the clocks
        m_MoveClock.restart();
        m_GameClock.restart();
        //open the game window
        startGame();
    }
    //load a file of the game
    else if (m_menu.getButton(Continue).getGlobalBounds().contains(location))
    {
        continueGame();

    }
    //exit the game
    if (m_menu.getButton(Exit).getGlobalBounds().contains(location))
    {
        m_window.close();
    }
}

//This function initializes the game
void GameControll::init()
{
    m_game_over = false;
    int number = 0;
    m_board.init();
    m_toolBar.init();
}

//This function serves as the main game loop
void GameControll::startGame()
{
    init();
    m_GameClock.restart();
    //As long as the user did not exit the game, this loop ran
    while (m_window.isOpen() && !m_game_over)
    {
        m_window.clear(WINDOW_COLOR);
        //Drawing the game board
        m_board.drawBoard(this->m_window);
        //Drawing the game menu on the board
        m_toolBar.drawToolBar(m_window);
        //fill Available vector 
        m_board.fillAvailableSticks();
        //update the game data 
        UpdateData();
        drawToolBar();
        m_window.display();

        //auto event = sf::Event{};
        //while (window->pollEvent(event))
        //{
        //Waiting for the user's action on the game board
        auto event = sf::Event{};
        while ( m_window.pollEvent(event))
        {
            switch (event.type)
            {
            //The user clicked the mouse
            case sf::Event::MouseButtonReleased:
            {
                auto location = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
                //Checking what action the user wants to do
                handleClick(location);
                break;

            }
            //Exit the game
            case sf::Event::Closed:
            {
                m_window.close();
                break;
            }
            }
        }
        //If the time runs out before the user has finished collecting 
        //all the sticks = he has lost
        if (m_GameClock.getElapsedTime().asSeconds() > 40)
        {
            //Loading next window
            m_youLose.setTexture(Resources::instance().getTexture(YouLose));
            m_youLose.scale(1.7f, 1.7f);
            m_window.clear(sf::Color::Color(0, 102, 102));
            m_window.draw(m_youLose);
            //Displaying the score in the new window
            m_toolBar.setScore(m_board.returnScore());
            m_window.draw(m_toolBar.getText(0));
            m_window.draw(m_toolBar.getNum(0));
            m_window.display();
            std::this_thread::sleep_for(std::chrono::seconds(5));
            //Exit the game
            m_window.close();
            break;
        }
        //f the user finished collecting all the sticks before the time 
        //ran out = he won
        if (m_board.returnSticksLeft() == 0)
        {
            //Loading next window
            m_youWin.setTexture(Resources::instance().getTexture(YouWin));
            m_youWin.scale(2.5f, 2.5f);
            m_window.clear(sf::Color::Color(0, 102, 102));
            m_window.draw(m_youWin);
            //Displaying the score in the new window
            m_toolBar.setScore(m_board.returnScore());
            m_window.draw(m_toolBar.getText(0));
            m_window.draw(m_toolBar.getNum(0));
            m_window.display();
            std::this_thread::sleep_for(std::chrono::seconds(5));
            //Exit the game
            m_window.close();
            break;
        }
        //Exit the game
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            m_window.close();
        }
    }
}

//This function hecking what action the user wants to do
void GameControll::handleClick(const sf::Vector2f& location)
{
    //Checking whether the user pressed one of the buttons in the game
    if (m_toolBar.getGlobalBounds().contains(location))
    {
        //Check if he clicked create file
        if (m_toolBar.isButtonPrasedSave(location))
        {
            m_board.createFile(m_ofile);
            return;
        }
        //Checking if he clicked on a hint
        else if (m_toolBar.isButtonPrasedHint(location))
        {
            m_board.hintPressed(m_window);
        }
    }
    //Checking if he pressed one of the sticks on the board
    else
    {
        m_board.findStick(location);
    }

}

//This function draws the game's Tool Bar
void GameControll::drawToolBar()
{
    for (int word = SCORE; word <= TIME; word++)
    {
        m_window.draw(m_toolBar.getText(word));
        m_window.draw(m_toolBar.getNum(word));
    }
}

//
void GameControll::continueGame()
{

}

//This function updates the details in the tool bar
void GameControll::UpdateData()
{
    m_toolBar.setScore(m_board.returnScore());
    m_toolBar.setSticksAvailable(m_board.returnSticksAva());
    m_toolBar.setSticksLeft(m_board.returnSticksLeft());
    m_toolBar.setSticksTake(m_board.returnSticksTake());
    m_toolBar.setTime(m_GameClock.getElapsedTime().asSeconds());
}


