#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Objects
{
private:
    float speed;
    Texture texture;
    Sprite sprite;

public:
    Objects(float x, float y, float s, Texture &texture)
        : sprite(texture)
    {
        sprite.setTexture(texture);
        sprite.setPosition({x, y});
        speed = s;
    }

    void moveLeft()
    {
        if (sprite.getPosition().x > 0)
        {
            sprite.move({-speed, 0});
        }
    }

    void moveRight()
    {
        if (sprite.getPosition().x < 1100.f)
        {
            sprite.move({speed, 0});
        }
    }

    void move(Vector2i mousePosition)
    {
        if (sprite.getPosition().x > 0 || sprite.getPosition().x < 1100)
        {
            sprite.setPosition({static_cast<float>(mousePosition.x)-47.f, sprite.getPosition().y});
        }
    }

    void setSpeed(float s){
        speed = s;
    }

    Sprite &getSprite()
    {
        return sprite;
    }
};