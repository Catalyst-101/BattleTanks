#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

using namespace sf;
using namespace std;

class Explosion {

    public:

        RectangleShape rectangle;
        int currentFrame;
        float animationSpeed;
        float elapsedTime;
        bool isFinished;

        Explosion() = default;

        Explosion(float x, float y) 
        {
            textures[0].loadFromFile("game/images/exp1.png");
            textures[1].loadFromFile("game/images/exp2.png"); 
            textures[2].loadFromFile("game/images/exp3.png"); 
            textures[3].loadFromFile("game/images/exp4.png"); 
            textures[4].loadFromFile("game/images/exp5.png"); 
            textures[5].loadFromFile("game/images/exp6.png");
            textures[6].loadFromFile("game/images/exp7.png");
            textures[7].loadFromFile("game/images/exp8.png");

            rectangle.setSize(Vector2f(70, 70));
            rectangle.setOrigin(50, 50); // Set origin to center
            rectangle.setPosition(x, y);
            rectangle.setTexture(&textures[0]);

            currentFrame = 0;
            animationSpeed = 0.01f;
            elapsedTime = 0.0f;
            isFinished = false;
        }

        void update(float deltaTime) 
        {
            if (isFinished) return;

            elapsedTime += deltaTime;

            if (elapsedTime >= animationSpeed) 
            {
                elapsedTime = 0.0f;
                currentFrame++;

                if (currentFrame < 8) 
                {
                    rectangle.setTexture(&textures[currentFrame]);
                }

                else 
                {
                    isFinished = true;
                }
            }
        }

        void draw(RenderWindow& window) 
        {
            if (!isFinished) 
            {
                window.draw(rectangle);
            }
        }

        bool finished() const 
        {
            return isFinished;
        }

    private:
        Texture textures[8];
};