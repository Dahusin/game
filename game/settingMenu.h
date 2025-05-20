#pragma once
#include <SFML/Graphics.hpp>
#include "classes/text.h"
#include <iostream>
using namespace sf;

bool settingMenu(RenderWindow &window, Font font, int &movingMode, int &shootingMode)
{
    Texture settingBgTexture("game/images/settingBackground.png");
    Sprite settingBgSprite(settingBgTexture);

    text movingModeText(L"ДВИЖЕНИЕ", 60, 138, 160);
    Text movingModeB(font);
    text movingModeButtons(movingModeB, L"КНОПКИ", 60, 770, 100);
    Text movingModeM(font);
    text movingModeMouse(movingModeM, L"МЫШЬ", 60, 800, 210);

    text shootingModeText(L"СТРЕЛЬБА", 60, 138, 520);
    Text shootingModeS(font);
    text shootingModeSpace(shootingModeS, L"ПРОБЕЛ", 60, 800, 460);
    Text shootingModeM(font);
    text shootingModeMouse(shootingModeM, L"МЫШЬ", 60, 800, 580);

    Text exitT(font);
    text exitText(exitT, L"ВЫХОД", 40, 75, 715);

    while (window.isOpen())
    {
        exitT.setFillColor(Color::White);
        int userChoice = 0;
        Vector2i mousePosition = Mouse::getPosition(window);
        if (exitT.getGlobalBounds().contains(Vector2f(mousePosition)))
        {
            exitT.setFillColor(Color(236, 161, 149));
            userChoice = 1;
        }
        if (movingMode == 1)
        {
            movingModeB.setFillColor(Color(236, 161, 149));
            movingModeM.setFillColor(Color::White);
        }
        else
        {
            movingModeM.setFillColor(Color(236, 161, 149));
            movingModeB.setFillColor(Color::White);
        }
        if (shootingMode == 1)
        {
            shootingModeS.setFillColor(Color(236, 161, 149));
            shootingModeM.setFillColor(Color::White);
        }
        else
        {
            shootingModeM.setFillColor(Color(236, 161, 149));
            shootingModeS.setFillColor(Color::White);
        }

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();
            if (event->is<Event::MouseButtonPressed>() || event->is<Event::KeyPressed>())
            {
                if (Mouse::isButtonPressed(Mouse::Button::Left))
                {
                    if (userChoice == 1 || Keyboard::isKeyPressed(Keyboard::Key::Escape))
                        return false;
                    if (movingModeB.getGlobalBounds().contains(Vector2f(mousePosition)))
                    {
                        movingMode = 1;
                    }
                    if (movingModeM.getGlobalBounds().contains(Vector2f(mousePosition)))
                    {
                        movingMode = 2;
                    }
                    if (shootingModeS.getGlobalBounds().contains(Vector2f(mousePosition)))
                    {
                        shootingMode = 1;
                    }
                    if (shootingModeM.getGlobalBounds().contains(Vector2f(mousePosition)))
                    {
                        shootingMode = 2;
                    }
                }
            }
        }
        window.clear();
        window.draw(settingBgSprite);
        window.draw(movingModeText.getText(font));
        window.draw(movingModeB);
        window.draw(movingModeM);
        window.draw(shootingModeText.getText(font));
        window.draw(shootingModeS);
        window.draw(shootingModeM);
        window.draw(exitT);
        window.display();
    }
    return false;
}