#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <string>

using namespace sf;
using namespace std;

class GameUI 
{
    private:

        // UI Elements
        RectangleShape background;
        RectangleShape info_box;
        RectangleShape ScoreBox;
        RectangleShape LiveBox;
        RectangleShape LevelBox;
        RectangleShape behind_info;
        Sprite battleground;

        // Text Elements
        Text Score;
        Text Live;
        Text Level;
        Text ep;

        // Resources
        Font font;
        Texture t1; // battleground
        Texture t2; // wall
        Texture t3; // infobox_bg
        Texture t4; // groundbrick
        Texture t5, t6; // tanks

        RectangleShape tk1, tk2;


    public:

        void GameUI_n(float window_width, float window_height) 
        {
            loadResources();
            initializeBoxes(window_width, window_height);
            initializeText();
        }

        void updateDisplays(int score, int lives, int level) 
        {
            Score.setString("Score : " + std::to_string(score));
            Live.setString("Lives : " + std::to_string(lives));
            Level.setString("Round : " + std::to_string(level));
        }

        void loadResources() 
        {
            // Load font
            font.loadFromFile("game/fonts/font1.ttf");

            // Load textures
            t1.loadFromFile("game/images/battleground.png");
            t2.loadFromFile("game/images/wall.png");
            t3.loadFromFile("game/images/infobox_bg.png");
            t4.loadFromFile("game/images/groundbrick.png");
            t5.loadFromFile("game/images/tank2.png");
            t6.loadFromFile("game/images/enemy.png");

            // Setup battleground
            battleground.setTexture(t1);
            battleground.setPosition(251, 2);
            battleground.setScale(0.5f, 0.6f);

            // Setup behind info
            behind_info.setSize(Vector2f(245, 395));
            behind_info.setTexture(&t3);
            behind_info.setPosition(4, 3);
        }

        void initializeBoxes(float window_width, float window_height) 
        {
            // Background
            background.setSize(Vector2f(window_width - 5, window_height - 5));
            background.setFillColor(Color(0, 0, 0, 0));
            background.setPosition(4, 3);
            background.setOutlineColor(Color::Black);
            background.setOutlineThickness(3);

            // Tanks Pictures
            tk1.setTexture(&t5);
            tk1.setSize(Vector2f(65, 80));
            tk1.setPosition(70, 170);
            tk1.setOrigin(32.5f, 40.0f);

            tk2.setTexture(&t6);
            tk2.setSize(Vector2f(70, 100));
            tk2.setPosition(170, 160);
            tk2.setOrigin(35, 50);

            ep.setFont(font);
            ep.setString("PLAYER         ENEMY");
            ep.setCharacterSize(25);
            ep.setFillColor(Color::Red);
            ep.setOutlineColor(Color::Black);
            ep.setOutlineThickness(2);
            ep.setPosition(42, 210);

            // Info Box
            info_box.setSize(Vector2f(245, 395));
            info_box.setFillColor(Color(5, 153, 33, 180));
            info_box.setPosition(4, 3);
            info_box.setOutlineColor(Color::Black);
            info_box.setOutlineThickness(3);

            // Score Box
            ScoreBox.setSize(Vector2f(230, 60));
            ScoreBox.setFillColor(Color(5, 100, 20));
            ScoreBox.setPosition(12, 12);
            ScoreBox.setOutlineColor(Color::Black);
            ScoreBox.setOutlineThickness(2);

            // Live Box
            LiveBox.setSize(Vector2f(230, 60));
            LiveBox.setFillColor(Color(5, 100, 20));
            LiveBox.setPosition(12, 330);
            LiveBox.setOutlineColor(Color::Black);
            LiveBox.setOutlineThickness(2);

            // Level Box
            LevelBox.setSize(Vector2f(230, 60));
            LevelBox.setFillColor(Color(5, 100, 20));
            LevelBox.setPosition(12, 260);
            LevelBox.setOutlineColor(Color::Black);
            LevelBox.setOutlineThickness(2);
        }

        void initializeText() 
        {
            // Score Text
            Score.setString("Score : 0");
            Score.setFont(font);
            Score.setCharacterSize(50);
            Score.setPosition(26, 10);
            Score.setFillColor(Color::White);
            Score.setOutlineColor(Color::Black);
            Score.setOutlineThickness(2);

            // Lives Text
            Live.setString("Lives : 3");
            Live.setFont(font);
            Live.setCharacterSize(50);
            Live.setPosition(26, 328);
            Live.setFillColor(Color::White);
            Live.setOutlineColor(Color::Black);
            Live.setOutlineThickness(2);

            // Level Text
            Level.setString("Round : 1");
            Level.setFont(font);
            Level.setCharacterSize(50);
            Level.setPosition(26, 258);
            Level.setFillColor(Color::White);
            Level.setOutlineColor(Color::Black);
            Level.setOutlineThickness(2);
        }

        void draw(RenderWindow& window) 
        {
            window.draw(battleground);
            window.draw(background);
            window.draw(behind_info);
            window.draw(info_box);
            window.draw(ScoreBox);
            window.draw(LiveBox);
            window.draw(LevelBox);
            window.draw(Score);
            window.draw(Live);
            window.draw(Level);
            window.draw(tk1);
            window.draw(tk2);
            window.draw(ep);
        }
};