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
    m_score[Player].setString("Player:\n" + std::to_string(number) + "%");
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
        //int numOfSticks = m_board.returnSticksLeft();
        m_board.fillAvailableStick();


        m_window.draw(m_score[0]);
        m_window.draw(m_score[1]);
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
            m_youLose.scale(0.8f, 0.8f);
            m_window.clear(sf::Color::Color(0, 102, 102));
            m_window.draw(m_youLose);
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
            m_board.hintPreesed();
        }
    }
    else
    {
        m_board.findStick(location);
    }

}

void GameControll::drawToolBar()
{
    for (int word = AVAILABLE; word <= TIME; word++)
    {
        m_window.draw(m_toolbar.getText(word));
        m_window.draw(m_toolbar.getNum(word));
    }
}

void GameControll::continueGame()
{

}


void GameControll::UpdateData()
{
    ////update the toolbar data
    //m_toolbar.SetScore(m_board.returnScore());
    m_toolbar.setSticksAvailable(m_board.returnSticksAva());
    m_toolbar.setSticksLeft(m_board.returnSticksLeft());
    m_toolbar.setSticksTake(m_board.returnSticksTake());
    m_toolbar.setTime(m_GameClock.getElapsedTime().asSeconds());
}



//void GameControll::locateObjects()
//{
// /*   for (int index = Player; index <= Computer; index++)
//    {
//        m_score[index].setFont(Resources::instance().getFont());
//        m_score[index].setCharacterSize(30);
//        m_score[index].setOutlineThickness(2);
//        m_score[index].setOutlineColor(sf::Color::Red);
//    }
//    int number = 0;
//    m_score[Player].setString("Player:\n" + std::to_string(number) + "%");
//    m_score[Computer].setString("Computer:\n" + std::to_string(number) + "%");
//
//    m_score[Player].setPosition(WINDOW_WIDTH * 0.05, WINDOW_HEIGHT * 0.88);
//    m_score[Computer].setPosition(WINDOW_WIDTH * 0.15, WINDOW_HEIGHT * 0.88);
//
//
//    sf::FloatRect win_bounds = m_YouWin.getLocalBounds();
//    float win_centerX = win_bounds.left + win_bounds.width / 2.0f;
//    float win_centerY = win_bounds.top + win_bounds.height / 2.0f;
//    m_YouWin.setOrigin(win_centerX, win_centerY);
//
//    sf::FloatRect lose_bounds = m_YouLose.getLocalBounds();
//    float lose_centerX = lose_bounds.left + lose_bounds.width / 2.0f;
//    float lose_centerY = lose_bounds.top + lose_bounds.height / 2.0f;
//    m_YouLose.setOrigin(lose_centerX, lose_centerY);
//
//    m_YouWin.setPosition(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.5);
//    m_YouLose.setPosition(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.5);*/
//
//}
