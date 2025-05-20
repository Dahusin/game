#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

class fallingObject
{
private:
    Texture texture;
    Sprite sprite;
    float speed;

public:
    fallingObject(float x, float y, Texture &texture)
        : sprite(texture)
    {

        sprite.setTexture(texture);
        sprite.setPosition({x, y});
        speed = 2.f;
    }

    fallingObject(float x, float y, Texture &texture, int speed)
        : sprite(texture)
    {
        sprite.setTexture(texture);
        sprite.setPosition({x, y});
        this->speed = speed;
    }

    void changePosition(float x)
    {
        sprite.setPosition({x, -20.f});
    }
    void update()
    {
        sprite.move({0.f, speed});
    }

    Sprite getSprite()
    {
        return sprite;
    }
};
