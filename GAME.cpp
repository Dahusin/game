#include "game/gamePlay.h"
#include "game/mainMenu.h"
#include "game/restartMenu.h"
#include "game/settingMenu.h"

int main()
{
    RenderWindow window(VideoMode({1200, 800}), "Meteor");
    Font font;
    int score = 0;
    int movingMode = 1;
    int shootingMode = 1;

    if (!font.openFromFile("PhantomMuff.ttf"))
    {
        std::cerr << "Error loading font" << std::endl;
        return false;
    }

    while (window.isOpen())
    {
        if (!mainMenu(window, font, movingMode, shootingMode))
        {
            break;
        }

        bool returnMenu = false;
        while (!returnMenu)
        {
            bool gameOver = false;
            while (!gameOver)
                gameOver = !gamePlay(window, font, score, movingMode, shootingMode);

            if (!restartGame(window, font, score, movingMode, shootingMode))
            {
                break;
            }
        }
    }
    return 0;
}