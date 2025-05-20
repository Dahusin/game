#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;

class text
{
private:
    std::wstring textString;
    int size;
    float x, y;

public:
    text(std::wstring textString, int size, float x, float y)
    {
        this->textString = textString;
        this->size = size;
        this->x = x;
        this->y = y;
    }
    text(Text &TEXT, std::wstring textString, int size, float x, float y)
    {
        TEXT.setString(textString);
        TEXT.setCharacterSize(size);
        TEXT.setPosition({x, y});
    }
    Text getText(Font font)
    {
        Text TEXT(font);
        TEXT.setString(textString);
        TEXT.setCharacterSize(size);
        TEXT.setPosition({x, y});
        return TEXT;
    }
};