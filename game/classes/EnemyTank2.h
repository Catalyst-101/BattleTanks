#pragma once

#include <SFML/Graphics.hpp>
#include "WallMap.h"
#include <cstdlib>
#include <ctime>
#include <math.h>

using namespace sf;

class EnemyTank2 {

private:

    Sprite enemyTank;         // Sprite for the tank
    Texture enemyTexture;     // Texture for the tank
    float speed;              // Tank movement speed
    int movementDirection;    // Current movement direction
    Clock movementTimer;      // Timer to handle periodic direction changes
    bool hasCollision;        // Tracks if the tank collided with a wall
    const float rotationSpeed = 2.0f;   // Rotation speed in degrees
    bool isForward;

public:

    // Constructor to initialize the tank
    EnemyTank2() 
    {
        if (!enemyTexture.loadFromFile("game/images/enemy.png")) {
            throw std::runtime_error("Failed to load enemy.png");
        }
        enemyTank.setTexture(enemyTexture);
        enemyTank.setScale(0.4f, 0.4f);
        FloatRect bounds = enemyTank.getLocalBounds();
        enemyTank.setOrigin(bounds.width / 2, bounds.height / 2); // Center origin for rotation
        speed = 0.7f;
        chooseRandomDirection();
        hasCollision = false;
        isForward = true;
    }

    void setPosition(float x, float y)
    {
        enemyTank.setPosition(x, y);
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
    void moveTank() 
    {

        if (movementTimer.getElapsedTime().asSeconds() > 1.0f) 
        {
            chooseRandomDirection();  // Change direction every second
            movementTimer.restart();
            hasCollision = false;
        }

        float angle = enemyTank.getRotation();
        float dx = cos(angle * 3.14159f / 180.0f) * speed;
        float dy = sin(angle * 3.14159f / 180.0f) * speed;

        switch (movementDirection) 
        {
            case 1: // Move Forward
                if (!hasCollision || !isForward)
                {
                    enemyTank.move(dy * speed, -dx * speed);
                    isForward = true;
                }
                else
                    undoMovement(speed);
                break;

            case 3: // Rotate Left
                enemyTank.rotate(-rotationSpeed);
                break;

            case 4: // Rotate Right
                enemyTank.rotate(rotationSpeed);
                break;

            case 5: // Move Backward
                if (!hasCollision || isForward)
                {
                    enemyTank.move(-dy * speed, dx * speed);
                    isForward = false;
                }
                else
                    undoMovement(-speed);
                break;
        }
    }

    // Draws the tank onto the window
    void draw(RenderWindow& window) {
        window.draw(enemyTank);
    }

    // Checks for collision with walls and updates the collision flag
    void checkCollision(WallMap& wallMap) {
        FloatRect tankBounds = enemyTank.getGlobalBounds();
        hasCollision = wallMap.checkCollision(tankBounds);
    }

    void undoMovement(float speed)
    {
        // Reverse the movement by a smaller amount
        float angle = enemyTank.getRotation();
        float dx = cos(angle * 3.14159f / 180.f);
        float dy = sin(angle * 3.14159f / 180.f);

        // Move back by a small fraction (e.g., 0.25 of the original speed)
        float reverseSpeed = speed * 0.25f * 4; // Adjust this value to change how much it "undoes"
        enemyTank.move(-dy * reverseSpeed, dx * reverseSpeed); // Move the tank back slightly
    }
};