#pragma once

#include "SFML/Graphics.hpp"
#include"SFML/Audio.hpp"


using namespace sf;

class Bullets {

    public:

        Bullets() 
        {
        }

        void setTexture()
        {
            t1.loadFromFile("game/images/bullet.png");
            bullet.setTexture(&t1);
        }

        void setSize(float x, float y)
        {
            bullet.setSize(Vector2f(x, y));
            bullet.setOrigin(x / 2, y / 2);
        }

        void fire(float speed)
        {
            bullet.move(direction.y * speed, -direction.x * speed);
        }

        //float getPos1(int choice)
        //{
        //    if (choice == 1) // Get Right
        //        return bullet.getPosition().x + bullet.getSize().x;
        //    else if (choice == 2) // Get Left
        //        return bullet.getPosition().x;
        //    else if (choice == 3) // Get Top
        //        return bullet.getPosition().y;
        //    else if (choice == 4) // Get Bottom
        //        return bullet.getPosition().y + bullet.getSize().y;

        //    return -1; // Default case for invalid input
        //}

        void draw_bullet(RenderWindow& window)
        {
            window.draw(bullet);
        }

        void setPos(Vector2f newPos)
        {
            bullet.setPosition(newPos);
        }

        void setDirection(Vector2f newDirection)
        {
            direction = newDirection;
        }

        bool isOffScreen(const Vector2u& screenSize)
        {
            // Check if the bullet is off the screen
            Vector2f pos = bullet.getPosition();
            return (pos.x + bullet.getSize().x < 0 || pos.x > screenSize.x ||
                pos.y + bullet.getSize().y < 0 || pos.y > screenSize.y);
        }

        FloatRect getBounds() const 
        {
            return bullet.getGlobalBounds(); // Return the global bounds of the bullet
        }

        void setRotation(float angle)
        {
            bullet.setRotation(angle);
        }

    private:

        RectangleShape bullet;
        Vector2f direction = { 1.0f, 0.0f }; // Default direction (rightward)
        Texture t1;
};
