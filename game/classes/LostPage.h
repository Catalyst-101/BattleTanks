#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include"Game.h"

using namespace sf;

class LostPage {

    private:

        SoundBuffer s1, s2, bt1;
        Sound losing, shooting, bt;
        Font font;
        Text loseText;
        RectangleShape bg;

        // Buttons
        RectangleShape restartButton;
        RectangleShape mainMenuButton;
        RectangleShape exitButton;
        Text restartText;
        Text mainMenuText;
        Text exitText;

        Texture t1;

    public:

        LostPage() 
        {
            bt1.loadFromFile("game/sounds/button_chng.ogg");
            bt.setBuffer(bt1);

            font.loadFromFile("game/fonts/font2.ttf");
            t1.loadFromFile("game/images/lose_bg.png");

            s1.loadFromFile("game/sounds/you_lose.ogg");
            losing.setBuffer(s1);
            s2.loadFromFile("game/sounds/battleground_s1.ogg");
            shooting.setBuffer(s2);

            // "You Lose" Text
            loseText.setFont(font);
            loseText.setString("You Lose!!");
            loseText.setCharacterSize(70);
            loseText.setFillColor(Color::Red);
            loseText.setOutlineColor(Color::Black);
            loseText.setOutlineThickness(4);

            FloatRect textBounds = loseText.getLocalBounds();
            loseText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
            loseText.setPosition(400, 120);

            // Background for Lost Page
            bg.setSize(Vector2f(800, 400));
            bg.setTexture(&t1);

            // Restart Button
            restartButton.setSize(Vector2f(200, 50));
            restartButton.setFillColor(Color(0, 100, 0, 150)); 
            restartButton.setPosition(300, 200); 
            restartButton.setOutlineColor(Color::Black);
            restartButton.setOutlineThickness(3);

            // Main Menu Button
            mainMenuButton.setSize(Vector2f(200, 50));
            mainMenuButton.setFillColor(Color(0, 100, 0, 150));  
            mainMenuButton.setPosition(300, 260);  
            mainMenuButton.setOutlineColor(Color::Black);
            mainMenuButton.setOutlineThickness(3);

            // Exit Button
            exitButton.setSize(Vector2f(200, 50));
            exitButton.setFillColor(Color(0, 100, 0, 150)); 
            exitButton.setPosition(300, 320);
            exitButton.setOutlineColor(Color::Black);
            exitButton.setOutlineThickness(3);

            // Button Text
            restartText.setFont(font);
            restartText.setString("RESTART");
            restartText.setCharacterSize(20);
            restartText.setFillColor(Color::White);
            restartText.setOutlineColor(Color::Black);
            restartText.setOutlineThickness(2);
            restartText.setPosition(335, 215);

            mainMenuText.setFont(font);
            mainMenuText.setString("MENU");
            mainMenuText.setCharacterSize(20);
            mainMenuText.setFillColor(Color::White);
            mainMenuText.setOutlineColor(Color::Black);
            mainMenuText.setOutlineThickness(2);
            mainMenuText.setPosition(357, 272);

            exitText.setFont(font);
            exitText.setString("EXIT");
            exitText.setCharacterSize(20);
            exitText.setFillColor(Color::White);
            exitText.setOutlineColor(Color::Black);
            exitText.setOutlineThickness(2);
            exitText.setPosition(365, 333);
        }

        void render(RenderWindow& window) 
        {
            window.draw(bg);
            window.draw(loseText);
            window.draw(restartButton);
            window.draw(mainMenuButton);
            window.draw(exitButton);
            window.draw(restartText);
            window.draw(mainMenuText);
            window.draw(exitText);
        }

        void play_sound() 
        {
            if (losing.getStatus() != Music::Playing) 
            {
                losing.play();
            }
            if (shooting.getStatus() != Music::Playing) 
            {
                shooting.play();
            }
        }

        void stop_sound() 
        {
            losing.stop();
            shooting.stop();
        }

        // Button handling logic
        void handle_buttons(RenderWindow& window, bool& play, bool& lose, bool& menu, Game& gameplay) 
        {
            Vector2i mousePos = Mouse::getPosition(window);

            if (restartButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && Mouse::isButtonPressed(Mouse::Left)) 
            {
                bt.play();
                play = true;
                lose = false;
                gameplay.resetGame();
                gameplay.resetScore();
                stop_sound();
            }

            else if (mainMenuButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && Mouse::isButtonPressed(Mouse::Left)) 
            {
                bt.play();
                menu = true;
                lose = false;
                stop_sound();
            }

            else if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && Mouse::isButtonPressed(Mouse::Left)) 
            {
                bt.play();
                window.close();
            }
        }
};
