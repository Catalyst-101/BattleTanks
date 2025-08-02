#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "Explosion.h"
#include "GameUI.h"
#include "EnemyTank1.h"
#include "WallMap.h"
#include "PlayerTank.h"

#include <iostream>

using namespace sf;
using namespace std;

class Game {

    public:

        Game(float window_width, float window_height) 
        {
            walls.rand_map(g_level);

            gameui.GameUI_n(window_width, window_height);
            // Initialize tank positions
            tank1.setPosition(320, 70);
            tank2.setPosition(320, 320);
            tank3.setPosition(720, 320);
            tank4.setPosition(720, 70);

            // Load game sound
            s1.loadFromFile("game/sounds/s1.ogg");
            b1.loadFromFile("game/sounds/battleground_s1.ogg");
            b2.loadFromFile("game/sounds/battleground_s2.ogg");
            b3.loadFromFile("game/sounds/battleground_s3.ogg");
            lo.loadFromFile("game/sounds/enemy_explosion.ogg");

            tank_s1.setBuffer(s1);
            b_1.setBuffer(b1);
            b_2.setBuffer(b2);
            b_3.setBuffer(b3);
            b_3.setVolume(30);

            bt1.loadFromFile("game/sounds/button_chng.ogg");
            bt.setBuffer(bt1);

            bt_2.loadFromFile("game/sounds/game_tp.ogg");
            bt2.setBuffer(bt1);

            lo.loadFromFile("game/sounds/lose_life.ogg");
            loselife.setBuffer(lo);

            pt.loadFromFile("game/sounds/point_gain.ogg");
            point.setBuffer(pt);
        }

        void button_sound() 
        {
            bt.play();
        }

        void draw_stuff(RenderWindow& window) 
        {
            gameui.draw(window);
            walls.draw(window);

            my_tank.print_tank(window);
            tank1.draw(window);
            tank2.draw(window);
            tank3.draw(window);
            tank4.draw(window);

            draw_explode(window); // Draw explosions
        }

        void movement(Event& gameEvent) 
        {
            FloatRect playerBounds = my_tank.my_tank.getGlobalBounds();
            my_tank.handleInput(gameEvent, walls.checkCollision(playerBounds));
        }

        void enemy_tank1(Event& event, RenderWindow& window) 
        {
            // Handle bullet updates for tanks
            tank1.update_bullets(walls, window);
            tank2.update_bullets(walls, window);
            tank3.update_bullets(walls, window);
            tank4.update_bullets(walls, window);

            // Move tanks and handle firing
            tank1.moveTank(walls, event, window);
            tank2.moveTank(walls, event, window);
            tank3.moveTank(walls, event, window);
            tank4.moveTank(walls, event, window);
        }

        void bullet1(Event& event) 
        {
            my_tank.bullet_firing(event);
        }

        void bullet2(RenderWindow& window) 
        {
            my_tank.update_and_draw_bullets(window, walls);
        }

        void resetGame() 
        {
            // Reset tank positions
            my_tank.my_tank.setPosition(510, 190);
            tank1.setPosition(320, 70);
            tank2.setPosition(320, 320);
            tank3.setPosition(720, 320);
            tank4.setPosition(720, 70);

            // Clear all bullets
            my_tank.bulletVec.clear();
            tank1.clearBullets();
            tank2.clearBullets();
            tank3.clearBullets();
            tank4.clearBullets();
        }

        void resetScore() 
        {
            // Reset game stats

            walls.resetMap();
            tank1.resetSpeed();
            tank2.resetSpeed();
            tank3.resetSpeed();
            tank4.resetSpeed();

            g_score = 0;
            g_live = 3;
            g_level = 1;
            gameui.updateDisplays(g_score, g_live, g_level);
        }

        void checkBulletColision(RenderWindow& window, bool& play, bool& lose)
        {

            Vector2f hitPos1 = tank1.getPos();

            if (my_tank.checkBulletCollisions(tank1)) 
            {
                handleTankHit(tank1);          
                triggerExplosion(hitPos1);        
            }

            Vector2f hitPos2 = tank2.getPos();

            if (my_tank.checkBulletCollisions(tank2))
            {
                handleTankHit(tank2);
                triggerExplosion(hitPos2);
            }

            Vector2f hitPos3 = tank3.getPos();

            if (my_tank.checkBulletCollisions(tank3)) 
            {
                handleTankHit(tank3);
                triggerExplosion(hitPos3);
            }

            Vector2f hitPos4 = tank4.getPos();

            if (my_tank.checkBulletCollisions(tank4)) 
            {
                handleTankHit(tank4);
                triggerExplosion(hitPos4);
            }

            Vector2f myPos = my_tank.getPos();

            if (tank1.bulletCollision(my_tank) || tank2.bulletCollision(my_tank) || tank3.bulletCollision(my_tank) || tank4.bulletCollision(my_tank)) 
            {
                triggerExplosion(myPos);

                g_live--;

                loselife.play();

                gameui.updateDisplays(g_score, g_live, g_level);

                if (g_live <= 0) {
                    play = false;
                    lose = true;
                }
            }
        }

        void checkRoundComplete() 
        {
            if (tank1.isReset() && tank2.isReset() && tank3.isReset() && tank4.isReset()) 
            {
                g_level++;
                gameui.updateDisplays(g_score, g_live, g_level);
                startNewRound();
            }
        }

        void startNewRound() 
        {
            walls.rand_map(g_level);
            bt2.play();
            resetGame();
        }

        void endgame(RenderWindow& window) 
        {
            window.close();
        }

        void play_bg() 
        {
            if (b_3.getStatus() != Music::Playing)
                b_3.play();
        }

        void stop_bg() 
        {
            b_3.stop();
            my_tank.stop_sounds();
        }

        void explode(float deltaTime) 
        {
            for (int i = 0; i < explosionCount; i++) 
            {
                explosions[i].update(deltaTime);

                if (explosions[i].finished()) 
                {
                    for (int j = i; j < explosionCount - 1; j++) 
                    {
                        explosions[j] = explosions[j + 1];
                    }

                    explosionCount--;
                    i--;
                }
            }
        }

        void draw_explode(RenderWindow& window) 
        {
            for (int i = 0; i < explosionCount; i++) 
            {
                explosions[i].draw(window);
            }
        }

        void triggerExplosion(Vector2f position) 
        {
            if (explosionCount < 10) 
            {
                explosions[explosionCount] = Explosion(position.x, position.y);
                explosionCount++;
            }
        }

        void handleTankHit(EnemyTank1& tank) 
        {
            g_score += 10;

            tank.increaseSpeed(g_level);
            point.play();

            gameui.updateDisplays(g_score, g_live, g_level);
            checkRoundComplete();
        }

    private:

        PlayerTank my_tank;
        EnemyTank1 tank1, tank2, tank3, tank4;
        WallMap walls;

        // Game sound
        SoundBuffer s1, b1, b2, b3, lo, bt1, bt_2, pt;
        Sound tank_s1, b_1, b_2, b_3, loselife, bt, bt2, point;

        // Game stats
        int g_score = 0;
        int g_live = 3;
        int g_level = 1;

        // Game UI
        GameUI gameui;

        // Explosion
        Explosion explosions[10];
        int explosionCount = 0;

};
