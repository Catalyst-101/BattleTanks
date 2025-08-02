#pragma once

#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"

#include"PlayerTank.h"
#include "Bullets.h"
#include "WallMap.h"

#include<iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace sf;
using namespace std;

class PlayerTank;

class EnemyTank1 {

private:

    Sprite enemyTank;
    Texture enemyTexture;
    int movementDirection;      // Current movement direction
    Clock movementTimer; 
    bool hasCollision;          // Tracks if the tank collided with a wall
    bool isForward;             // Tracks if the tank is moving forward or backward
    bool resetState = false;    // Track if tank is reset

    float speed = 0.7f;          // Tank movement speed
    float bul_speed = 3.0f;      // Bullet Speed
    float rotationSpeed = 2.0f;  // Rotation speed in degrees

    Bullets newBullet;
    bool BulletisFiring = false;    // bool to track bullet firing status
    vector<Bullets> bulletVec;      // Vector to store bullets
    Clock shootingTimer;            // Add timer for automatic shooting
    const float SHOOT_COOLDOWN = 1.0f;

    SoundBuffer s1, s2, s3;
    Sound explode, laser;

public:

    EnemyTank1() {

        newBullet.setTexture(); //user defined
        enemyTexture.loadFromFile("game/images/enemy.png");

        s1.loadFromFile("game/sounds/enemy_explosion.ogg");
        s2.loadFromFile("game/sounds/laser.ogg");
        s3.loadFromFile("game/sounds/tank_move.ogg");

        explode.setBuffer(s1);
        laser.setBuffer(s2);
        laser.setVolume(15);

        enemyTank.setTexture(enemyTexture);
        enemyTank.setScale(0.3f, 0.3f);
        FloatRect bounds = enemyTank.getLocalBounds();
        enemyTank.setOrigin(bounds.width / 2, bounds.height / 2); // Center origin for rotation

        chooseRandomDirection();
        hasCollision = false;
        isForward = true;
        shootingTimer.restart();
        resetState = false;
    }

    void increaseSpeed(int level)
    {
        if (level % 2 == 0)
        {
            speed += 0.08f;
            rotationSpeed += 0.05f;
            bul_speed += 0.08f;
        }
    }

    Vector2f getPos()
    {
        return enemyTank.getPosition();
    }

    void resetSpeed()
    {
        speed = 0.7f;
        rotationSpeed = 2.0f;
        bul_speed = 3.0f;
    }

    void setPosition(float x, float y) 
    {
        enemyTank.setPosition(x, y);
        resetState = false;  // Tank is active when position is set
    }

    bool isReset() const 
    {
        return resetState;
    }

    // Randomly picks a movement direction
    void chooseRandomDirection() 
    {
        int randomNum = rand() % 100;

        if (randomNum < 45)
            movementDirection = 1;  // Forward
        else if (randomNum < 60)
            movementDirection = 3;  // Rotate Left
        else if (randomNum < 75)
            movementDirection = 4;  // Rotate Right
        else
            movementDirection = 5;  // Backward
    }

    // Moves the tank based on its direction and handles collisions
    void moveTank(WallMap& wallMap, Event& event, RenderWindow& window) 
    {
        if (movementTimer.getElapsedTime().asSeconds() > 1.5f) 
        {
            chooseRandomDirection();
            movementTimer.restart();
        }

        float angle = enemyTank.getRotation();
        float dx = cos(angle * 3.14159f / 180.0f) * speed;
        float dy = sin(angle * 3.14159f / 180.0f) * speed;

        FloatRect tankBounds = enemyTank.getGlobalBounds();
        Vector2f oldPos = enemyTank.getPosition();

        switch (movementDirection)
        {
            case 1: // Move Forward
                enemyTank.move(dy * speed, -dx * speed);
                if (wallMap.checkCollision(enemyTank.getGlobalBounds())) 
                {
                    enemyTank.setPosition(oldPos);
                    chooseRandomDirection(); // Change direction when hitting wall
                }
                //move.play(); 

                isForward = true;
                break;

            case 3: // Rotate Left
                enemyTank.rotate(-rotationSpeed);
                //move.play();
                break;

            case 4: // Rotate Right
                enemyTank.rotate(rotationSpeed);
                //move.play();
                break;

            case 5: // Move Backward
                enemyTank.move(-dy * speed, dx * speed);
                if (wallMap.checkCollision(enemyTank.getGlobalBounds()))
                {
                    enemyTank.setPosition(oldPos);
                    chooseRandomDirection();
                }
                //move.play(); 

                isForward = false;
                break;
        }

        bullet_firing();
        update_bullets(wallMap, window);
    }

    // Draw the tank onto the window
    void draw(RenderWindow& window) 
    {
        window.draw(enemyTank);
        //move.play();
        // Draw all bullets
        for (auto& bullet : bulletVec) 
        {
            bullet.draw_bullet(window);
            laser.play();
        }
    }

    // Undo movement
    void undoMovement(float speed) 
    {
        float angle = enemyTank.getRotation();
        float dx = cos(angle * 3.14159f / 180.f);
        float dy = sin(angle * 3.14159f / 180.f);

        float reverseSpeed = speed * 2.0f; 

        if (isForward) 
        {
            enemyTank.move(-dy * reverseSpeed, dx * reverseSpeed);
        }

        else 
        {
            enemyTank.move(dy * reverseSpeed, -dx * reverseSpeed);
        }
    }

    // Handle bullet firing
    void bullet_firing() 
    {
        if (shootingTimer.getElapsedTime().asSeconds() >= SHOOT_COOLDOWN) 
        {
            shootingTimer.restart();

            float angle = enemyTank.getRotation();
            Vector2f direction(cos(angle * 3.14159f / 180.f), sin(angle * 3.14159f / 180.f));

            // Set bullet position
            Vector2f tankPos = enemyTank.getPosition();
            Vector2f bulletPos = tankPos;

            newBullet.setSize(5, 15);
            newBullet.setPos(bulletPos);
            newBullet.setDirection(direction);
            newBullet.setRotation(angle);

            bulletVec.push_back(newBullet);
        }
    }

    // Bullet firing
    void update_bullets(WallMap& wallMap, RenderWindow& window) 
    {
        for (auto it = bulletVec.begin(); it != bulletVec.end();) 
        {
            it->fire(bul_speed);

            if (wallMap.checkCollision(it->getBounds()) || it->isOffScreen(window.getSize())) 
            {
                it = bulletVec.erase(it);
            }

            else 
            {
                ++it;
            }
        }
    }

    void clearBullets() 
    {
        bulletVec.clear();
        shootingTimer.restart();
    }

    FloatRect getTankBounds() const 
    {
        return enemyTank.getGlobalBounds();
    }

    void resetPosition() 
    {
        explode.play();
        enemyTank.setPosition(40000, 40000);
        clearBullets(); // Clear any existing bullets
        resetState = true;  // Set reset state when tank is destroyed
    }

    bool bulletCollision(PlayerTank& player);
};