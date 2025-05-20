#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
class Bullet

{
private:
    Texture texture;
    Sprite sprite;
    float speed;

public:
    Bullet(float x, float y, Texture& texture)
    : sprite(texture)
    {
        sprite.setTexture(texture);
        sprite.setPosition({x, y});
        speed = 10.f;
    }

    void update()
    {
        sprite.move({0.f, -speed});
    }

    Sprite getSprite()
    {
        return sprite;
    }
};