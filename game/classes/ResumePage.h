#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "Game.h"

using namespace sf;

class ResumePage {

    private:

        Font font;
        Text titleText;
        RectangleShape bg;

        // Buttons
        RectangleShape resumeButton;
        RectangleShape mainMenuButton;
        Text resumeText;
        Text mainMenuText;

        Texture t1;
        SoundBuffer s1, bt1;
        Sound bg_s, bt;

    public:

        ResumePage() 
        {
            bt1.loadFromFile("game/sounds/button_chng.ogg");
            bt.setBuffer(bt1);
            font.loadFromFile("game/fonts/font2.ttf");
            t1.loadFromFile("game/images/menu.png");
            s1.loadFromFile("game/sounds/menu_song.ogg");

            bg_s.setBuffer(s1);

            // Title Text
            titleText.setFont(font);
            titleText.setString("BattleTanks");
            titleText.setCharacterSize(70);
            titleText.setFillColor(Color::Green);
            titleText.setOutlineColor(Color::Black);
            titleText.setOutlineThickness(4);

            FloatRect textBounds = titleText.getLocalBounds();
            titleText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
            titleText.setPosition(400, 120); 

            // Background for Resume Page
            bg.setSize(Vector2f(800, 400));
            bg.setFillColor(Color::White);
            bg.setTexture(&t1);

            // Resume Button
            resumeButton.setSize(Vector2f(200, 50));
            resumeButton.setFillColor(Color(0, 100, 0, 150));  // Dark Green
            resumeButton.setPosition(300, 200); 
            resumeButton.setOutlineColor(Color::Black);
            resumeButton.setOutlineThickness(3);

            // Main Menu Button
            mainMenuButton.setSize(Vector2f(200, 50));
            mainMenuButton.setFillColor(Color(0, 100, 0, 150));  // Dark Green
            mainMenuButton.setPosition(300, 260);
            mainMenuButton.setOutlineColor(Color::Black);
            mainMenuButton.setOutlineThickness(3);

            // Button Text
            resumeText.setFont(font);
            resumeText.setString("RESUME");
            resumeText.setCharacterSize(20);
            resumeText.setFillColor(Color::White);
            resumeText.setOutlineColor(Color::Black);
            resumeText.setOutlineThickness(2);
            resumeText.setPosition(335, 215);

            mainMenuText.setFont(font);
            mainMenuText.setString("MENU");
            mainMenuText.setCharacterSize(20);
            mainMenuText.setFillColor(Color::White);
            mainMenuText.setOutlineColor(Color::Black);
            mainMenuText.setOutlineThickness(2);
            mainMenuText.setPosition(355, 273);
        }

        void render(RenderWindow& window)
        {
            window.draw(bg);
            window.draw(titleText);
            window.draw(resumeButton);
            window.draw(mainMenuButton);
            window.draw(resumeText);
            window.draw(mainMenuText);
        }

        // Button handling logic
        void handle_buttons(RenderWindow& window, bool& play, bool& resume, bool& menu, Game& gameplay) 
        {
            Vector2i mousePos = Mouse::getPosition(window);

            if (resumeButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && Mouse::isButtonPressed(Mouse::Left)) 
            {
                bt.play();
                play = true;
                resume = false;
            }

            else if (mainMenuButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && Mouse::isButtonPressed(Mouse::Left)) 
            {
                bt.play();
                menu = true;
                resume = false;
            }
        }

        void sound_play()
        {
            if (bg_s.getStatus() != Music::Playing)
                bg_s.play();
        }

        void sound_stop()
        {
            bg_s.stop();
        }
};

