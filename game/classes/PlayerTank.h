#pragma once

#include <SFML/Graphics.hpp>
#include"SFML/Audio.hpp"

#include"WallMap.h"
#include"Bullets.h"

#include <cmath>
#include<vector>

using namespace sf;
using namespace std;

class EnemyTank1;

class PlayerTank {

    public:

        vector<Bullets> bulletVec;
        Sprite my_tank;

        PlayerTank() 
        {
            newBullet.setTexture(); //user defined

            s1.loadFromFile("game/sounds/shoot1.ogg");
            s2.loadFromFile("game/sounds/turret.ogg");
            s3.loadFromFile("game/sounds/tank_move.ogg");
            s4.loadFromFile("game/sounds/enemy_explosion.ogg");
            s5.loadFromFile("game/sounds/lose_life.ogg");

            turret.setBuffer(s2);
            move.setBuffer(s3);
            move.setVolume(20);
            explode.setBuffer(s4);
            loselife.setBuffer(s5);


            shoot.setBuffer(s1);
            shoot.setVolume(35);
            t1.loadFromFile("game/images/tank2.png");

            // Set the texture for the tank
            my_tank.setTexture(t1);
            my_tank.setPosition(523, 198); // Initial position
            my_tank.setScale(0.25f, 0.25f); // Scale the tank
            // Set origin to the center of the tank
            FloatRect tankBounds = my_tank.getLocalBounds();
            my_tank.setOrigin(tankBounds.width / 2, tankBounds.height / 2);
        }

        void handleInput(Event& gameEvent, bool col)
        {
            col2 = col;

            speed = 5.0f;
            float angle = my_tank.getRotation();

            if (gameEvent.type == sf::Event::KeyPressed) 
            {
                if (gameEvent.key.code == sf::Keyboard::Up) 
                {
                    // Move forward
                    if (!col || !isForward) 
                    {
                        moveTank(speed);
                        isForward = true;
                    }
                    else if (isForward) 
                    {
                        undoMovement(speed);
                    }

                    if (move.getStatus() != sf::Sound::Playing) 
                    {
                        move.play();
                    }
                }

                else if (gameEvent.key.code == sf::Keyboard::Down) 
                {
                    // Move backward
                    if (!col || isForward) 
                    {
                        moveTank(-speed);
                        isForward = false;
                    }

                    else if (!isForward) 
                    {
                        undoMovement(-speed);
                    }

                    if (move.getStatus() != sf::Sound::Playing) 
                    {
                        move.play();
                    }
                }

                else if (gameEvent.key.code == sf::Keyboard::Left) 
                {
                    // Rotate left
                    my_tank.rotate(-5);
                    if (turret.getStatus() != sf::Sound::Playing) 
                    {
                        turret.play();
                    }
                }

                else if (gameEvent.key.code == sf::Keyboard::Right) 
                {
                    // Rotate right
                    my_tank.rotate(5);
                    if (turret.getStatus() != sf::Sound::Playing) 
                    {
                        turret.play();
                    }
                }
            }

            if (gameEvent.type == sf::Event::KeyReleased) 
            {
                if (gameEvent.key.code == sf::Keyboard::Up || gameEvent.key.code == sf::Keyboard::Down) 
                {
                    move.stop(); // Stop movement sound when W or S is released
                }

                else if (gameEvent.key.code == sf::Keyboard::Left || gameEvent.key.code == sf::Keyboard::Right) 
                {
                    turret.stop(); // Stop turret sound when A or D is released
                }
            }
        }

        void moveTank(float speed) 
        {
            float angle = my_tank.getRotation();
            float dx = cos(angle * 3.14159f / 180.f);
            float dy = sin(angle * 3.14159f / 180.f);

            my_tank.move(dy * speed, -dx * speed);
        }

        void print_tank(RenderWindow& window)
        {
            window.draw(my_tank);
        }

        void undoMovement(float speed) 
        {
            float angle = my_tank.getRotation();
            float dx = cos(angle * 3.14159f / 180.f);
            float dy = sin(angle * 3.14159f / 180.f);

            float reverseSpeed = speed * 0.25f * 4;
            my_tank.move(-dy * reverseSpeed, dx * reverseSpeed);
        }

        // ------------------------------------------------------------------------------------------------------->

        void bullet_firing(Event& event)
        {
            static int lastFiredTime = 0;
            int currentTime = time(0);

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) 
            {
                if (!BulletisFiring && (currentTime - lastFiredTime >= 1)) 
                {
                    if(!col2)
                        undoMovement(speed);

                    BulletisFiring = true;
                    lastFiredTime = currentTime;

                    shoot.play();

                    float angle = my_tank.getRotation();
                    Vector2f direction(cos(angle * 3.14159f / 180.f), sin(angle * 3.14159f / 180.f));
                        
                    Vector2f tankPos = my_tank.getPosition();
                    //Vector2f bulletPos = tankPos + bulletSpa23+wnOffset;

                    newBullet.setSize(5, 15);
                    newBullet.setPos(tankPos);
                    newBullet.setDirection(direction);
                    newBullet.setRotation(angle);

                    bulletVec.push_back(newBullet);

                    BulletisFiring = false;
                }
            }
        }

        void update_and_draw_bullets(RenderWindow& window, WallMap& wallMap)
        {
            // Iterate through the bullets and update/draw them
            for (auto it = bulletVec.begin(); it != bulletVec.end(); ) 
            {
                it->fire(10.0f); // Update bullet's position (pass speed as argument)
                it->draw_bullet(window); // Draw the bullet

                // Check if the bullet collides with the wall
                if (wallMap.checkCollision(it->getBounds())) 
                {
                    it = bulletVec.erase(it); // If collided, remove the bullet from the vector
                }

                // Remove the bullet if it goes off-screen
                else if (it->isOffScreen(Vector2u(window.getSize()))) 
                {
                    it = bulletVec.erase(it); // Safely erase the bullet from the vector
                }

                else 
                {
                    ++it; // Move to the next bullet
                }
            }
        }

        //--------------------------------------------------------------------------------------------------

        FloatRect getTankBounds() const 
        {
            return my_tank.getGlobalBounds();
        }
            
        Vector2f getPos()
        {
            return my_tank.getPosition();
        }

        void resetPosition() 
        {
            explode.play();
            my_tank.setPosition(523, 198); // Reset to initial position
            bulletVec.clear(); // Clear any existing bullets
        }

        bool checkBulletCollisions(EnemyTank1& enemy);

        void stop_sounds()
        {
            shoot.stop();
            turret.stop();
            move.stop();
            explode.stop();
            loselife.stop();
        }

    private:

        Texture t1;
        SoundBuffer s1, s2, s3, s4, s5;
        Sound shoot, turret, move, explode, loselife;

        bool isForward = true;
        bool BulletisFiring = false;
        bool col2;
        
        Bullets newBullet;

        float speed;

};


