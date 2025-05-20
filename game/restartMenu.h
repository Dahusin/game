#pragma once
#include <SFML/Graphics.hpp>
#include "settingMenu.h"
#include <iostream>
using namespace sf;

bool restartGame(RenderWindow &window, Font font, int &score, int &goal, int &movingMode, int &shootingMode)
{
    Text gameoverText(font);
    gameoverText.setString(L"  ТЫ ПРОИГРАЛ\nОЧКИ: " + std::to_string(score));
    gameoverText.setCharacterSize(60);
    gameoverText.setPosition({370, 100});

    Text winText(font);
    winText.setString(L"ТЫ СПРАВИЛСЯ");
    winText.setCharacterSize(60);
    winText.setPosition({370, 100});

    Text restartText(font);
    restartText.setString(L"ЗАНОВО");
    restartText.setCharacterSize(60);
    restartText.setPosition({470, 360});

    Text nextText(font);
    nextText.setString(L"ДАЛЕЕ");
    nextText.setCharacterSize(60);
    nextText.setPosition({470, 360});

    Text settingText(font);
    settingText.setString(L"НАСТРОЙКИ");
    settingText.setCharacterSize(60);
    settingText.setPosition({470, 510});

    Text exitText(font);
    exitText.setString(L"ВЫХОД");
    exitText.setCharacterSize(60);
    exitText.setPosition({520, 660});

    Texture rmBgTexture("game/images/rmBackground.png");
    Sprite rmBgSprite(rmBgTexture);

    while (window.isOpen())
    {
        restartText.setFillColor(Color::White);
        settingText.setFillColor(Color::White);
        exitText.setFillColor(Color::White);

        Vector2i mousePosition = Mouse::getPosition(window);

        if (restartText.getGlobalBounds().contains(Vector2f(mousePosition)))
        {
            restartText.setFillColor(Color(236, 161, 149));
        }
        if (winText.getGlobalBounds().contains(Vector2f(mousePosition)))
        {
            winText.setFillColor(Color(236, 161, 149));
        }
        if (settingText.getGlobalBounds().contains(Vector2f(mousePosition)))
        {
            settingText.setFillColor(Color(236, 161, 149));
        }
        if (exitText.getGlobalBounds().contains(Vector2f(mousePosition)))
        {
            exitText.setFillColor(Color(236, 161, 149));
        }

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();

            if (event->is<Event::KeyPressed>())
            {
                if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
                {
                    return true;
                }
                if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
                {
                    return false;
                }
            }
            if (event->is<Event::MouseButtonPressed>())
            {
                if (Mouse::isButtonPressed(Mouse::Button::Left))
                {
                    if (restartText.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window))) || winText.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window))))
                    {
                        return true;
                    }
                    if (settingText.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window))))
                    {
                        if (!settingMenu(window, font, movingMode, shootingMode))
                            break;
                    }
                    if (exitText.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window))))
                    {
                        return false;
                    }
                }
            }
        }

        window.clear();
        window.draw(rmBgSprite);
        if (score + 10 == goal)
        {
            window.draw(winText);
            window.draw(nextText);
        }
        else
        {
            window.draw(gameoverText);
            window.draw(restartText);
        }

        window.draw(settingText);
        window.draw(exitText);
        window.display();
    }

    return false;
}