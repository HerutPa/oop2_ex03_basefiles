#include "GameControll.h"
#include <iostream>

GameControll::GameControll()
    :m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pick Up Sticks"), m_game_over(false)
{
    m_window.setFramerateLimit(60);
    m_YouWin.setTexture(Resources::instance().getTexture(YouWin));
    m_YouLose.setTexture(Resources::instance().getTexture(YouLose));    // locateObjects();
}

void GameControll::run()
{
    m_GameClock.restart();

    while (m_window.isOpen())
    {
        m_window.clear(sf::Color::Color(0, 0, 0));
        m_menu.drawMenu(this->m_window);
        m_window.display();
        float deltaTime = m_GameClock.restart().asSeconds();

        // auto delta_Time = m_MoveClock.restart();
        if (auto event = sf::Event{}; m_window.waitEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
            {
                m_window.close();
                break;
            }
            case sf::Event::MouseButtonReleased:
            {
                auto location = m_window.mapPixelToCoords(
                    { event.mouseButton.x, event.mouseButton.y });
                handleMenuClick(location);
                break;
            }
            case sf::Event::MouseMoved:
            {
                auto location = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
                handleMenuMouseMoved(location);
            }

            }

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            m_window.close();
        }
    }
}

void GameControll::handleMenuMouseMoved(const sf::Vector2f location)
{
    for (int button = Play; button <= Exit; button++)
    {
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

void GameControll::handleMenuClick(const sf::Vector2f location)
{
    if (m_menu.getButton(Play).getGlobalBounds().contains(location))
    {
        m_MoveClock.restart();
        m_GameClock.restart();
        startGame();
    }
    else if (m_menu.getButton(Continue).getGlobalBounds().contains(location))
    {
        continueGame();

    }
    if (m_menu.getButton(Exit).getGlobalBounds().contains(location))
    {
        m_window.close();
    }
}

void GameControll::init()
{
    m_game_over = false;
    int number = 0;
    m_board.init();
    m_toolBar.init();
}


void GameControll::startGame()
{
    init();
    m_GameClock.restart();
    while (m_window.isOpen() && !m_game_over)
    {
        m_window.clear(WINDOW_COLOR);
        m_board.drawBoard(this->m_window);
        m_toolBar.drawToolBar(m_window);
        m_board.fillAvailableSticks();
        UpdateData();
        drawToolBar();
        m_window.display();


        //auto event = sf::Event{};
        //while (window->pollEvent(event))
        //{

        auto event = sf::Event{};
        while ( m_window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::MouseButtonReleased:
            {
                auto location = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
                handleClick(location);
                break;

            }
            //case sf::Event::MouseMoved:
            //{
            //    auto location = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
            //    //handleGameMouseMoved(location);
            //    break;
            //}

            case sf::Event::Closed:
            {
                m_window.close();
                break;
            }
            }
        }

        if (m_GameClock.getElapsedTime().asSeconds() > 40)
        {
            m_youLose.setTexture(Resources::instance().getTexture(YouLose));
            m_youLose.scale(1.7f, 1.7f);
            m_window.clear(sf::Color::Color(0, 102, 102));
            m_window.draw(m_youLose);

            m_toolBar.setScore(m_board.returnScore());
            m_window.draw(m_toolBar.getText(0));
            m_window.draw(m_toolBar.getNum(0));

            m_window.display();
            std::this_thread::sleep_for(std::chrono::seconds(5));
            m_window.close();
            break;
        }

        if (m_board.returnSticksLeft() == 0)
        {
            m_youWin.setTexture(Resources::instance().getTexture(YouWin));
            m_youWin.scale(2.5f, 2.5f);
            m_window.clear(sf::Color::Color(0, 102, 102));
            m_window.draw(m_youWin);

            m_toolBar.setScore(m_board.returnScore());
            m_window.draw(m_toolBar.getText(0));
            m_window.draw(m_toolBar.getNum(0));

            m_window.display();
            std::this_thread::sleep_for(std::chrono::seconds(5));

            m_window.close();
            break;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            m_window.close();
        }
    }
}

void GameControll::handleClick(const sf::Vector2f& location)
{
    if (m_toolBar.getGlobalBounds().contains(location))
    {
        if (m_toolBar.isButtonPrasedSave(location))
        {
            m_board.createFile(m_ofile);
            return;
        }
        else if (m_toolBar.isButtonPrasedHint(location))
        {
            m_board.hintPressed(m_window);
        }
    }
    else
    {
        m_board.findStick(location);
    }

}

void GameControll::drawToolBar()
{
    for (int word = SCORE; word <= TIME; word++)
    {
        m_window.draw(m_toolBar.getText(word));
        m_window.draw(m_toolBar.getNum(word));
    }
}

void GameControll::continueGame()
{

}


void GameControll::UpdateData()
{
    ////update the toolbar data
    m_toolBar.setScore(m_board.returnScore());
    m_toolBar.setSticksAvailable(m_board.returnSticksAva());
    m_toolBar.setSticksLeft(m_board.returnSticksLeft());
    m_toolBar.setSticksTake(m_board.returnSticksTake());
    m_toolBar.setTime(m_GameClock.getElapsedTime().asSeconds());
}


