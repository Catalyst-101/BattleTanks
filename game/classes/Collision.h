#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

using namespace sf;

class Collision {
    
    public:

        static bool CheckCollision(sf::Sprite& sprite1, sf::Sprite& sprite2) {
            
            FloatRect bounds1 = sprite1.getGlobalBounds();
            FloatRect bounds2 = sprite2.getGlobalBounds();

            Vector2f sprite1Center(bounds1.left + bounds1.width / 2.0f, bounds1.top + bounds1.height / 2.0f);
            Vector2f sprite2Center(bounds2.left + bounds2.width / 2.0f, bounds2.top + bounds2.height / 2.0f);

            Vector2f halfSize1(bounds1.width / 2.0f, bounds1.height / 2.0f);
            Vector2f halfSize2(bounds2.width / 2.0f, bounds2.height / 2.0f);

            float deltaX = sprite2Center.x - sprite1Center.x;
            float deltaY = sprite2Center.y - sprite1Center.y;

            float intersectX = std::abs(deltaX) - (halfSize1.x + halfSize2.x);
            float intersectY = std::abs(deltaY) - (halfSize1.y + halfSize2.y);

            if (intersectX < 0.0f && intersectY < 0.0f) 
                return true;

            return false;
        }
};

