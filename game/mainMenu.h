#pragma once
#include <SFML/Graphics.hpp>
#include "settingMenu.h"
#include "classes/text.h"
using namespace sf;

bool mainMenu(RenderWindow &window, Font font, int &movingMode, int &shootingMode)
{
    Texture menuBgTexture("game/images/menuBackground2.png");
    Sprite menuBg(menuBgTexture);

    text nameTextF(L"METEOR", 80, 160, 40);
    text nameTextS(L"BLAST", 80, 200, 110);

    Text playT(font);
    text playText(playT, L"СТАРТ", 60, 225, 300);

    Text settingT(font);
    text settingText(settingT, L"НАСТРОЙКИ", 60, 165, 425);

    Text exitT(font);
    text exitText(exitT, L"ВЫХОД", 60, 230, 660);

    while (window.isOpen())
    {
        playT.setFillColor(Color::White);
        settingT.setFillColor(Color::White);
        exitT.setFillColor(Color::White);

        int userChoice = 0;
        Vector2i mousePosition = Mouse::getPosition(window);

        if (playT.getGlobalBounds().contains(Vector2f(mousePosition)))
        {
            playT.setFillColor(Color(236, 161, 149));
            userChoice = 1;
        }
        if (settingT.getGlobalBounds().contains(Vector2f(mousePosition)))
        {
            settingT.setFillColor(Color(236, 161, 149));
            userChoice = 2;
        }
        if (exitT.getGlobalBounds().contains(Vector2f(mousePosition)))
        {
            exitT.setFillColor(Color(236, 161, 149));
            userChoice = 3;
        }
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();
            if (event->is<Event::MouseButtonPressed>() || event->is<Event::KeyPressed>())
            {
                if ((Mouse::isButtonPressed(Mouse::Button::Left) && userChoice == 1) || Keyboard::isKeyPressed(Keyboard::Key::Enter))
                {
                    return true;
                }
                if ((Mouse::isButtonPressed(Mouse::Button::Left) && userChoice == 2))
                {
                    if (!settingMenu(window, font, movingMode, shootingMode))
                        break;
                }
                if ((Mouse::isButtonPressed(Mouse::Button::Left) && userChoice == 3) || Keyboard::isKeyPressed(Keyboard::Key::Escape))
                {
                    return false;
                }
            }
        }

        window.clear();
        window.draw(menuBg);
        window.draw(nameTextF.getText(font));
        window.draw(nameTextS.getText(font));
        window.draw(playT);
        window.draw(settingT);
        window.draw(collectionT);
        window.draw(exitT);
        window.display();
    }

    return false;
}