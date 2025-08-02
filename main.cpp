#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "game/classes/GameMenu.h"
#include "game/classes/Options.h"
#include "game/classes/Game.h"
#include "game/classes/EnemyTank.h"
#include "game/classes/DifTank.h"
#include "game/classes/LostPage.h"
#include "game/classes/ResumePage.h"

#include <iostream>
#include <ctime>
#include <string>

using namespace sf;
using namespace std;

int main() {

    Clock cloak;

    // Screen Width and Height
    int window_width = 800;
    int window_height = 400;

    RenderWindow window(VideoMode(window_width, window_height), "Battle Tanks", Style::Default);

    window.setFramerateLimit(60);

    //float deltaTime = cloak.restart().asSeconds();

    // GameMenu -->
    GameMenu gamemenu;

    // Game Options -->
    Options options(window_width, window_height);

    // Game Play -->
    Game gameplay(800.0f, 400.0f);

    // Lost Page -->
    LostPage lostpage;

    // Resume Page -->
    ResumePage resumepage;

    // Tank Viewer -->
    DifTank tankveiwer;

    // Bools to track different Pages
    bool play = false;
    bool options_ = false;
    bool gameOver = false;
    bool view_dif = false;
    bool lose = false;
    bool lostSoundPlayed = false;  // Sound bool for lost page
    bool resume = false;

    bool menu = !options_ && !play && !view_dif && !lose && !resume;


    while (window.isOpen()) 
    {
        Event event;

        while (window.pollEvent(event)) 
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right) 
            {
                Vector2i mousePos = Mouse::getPosition(window);
                cout << "Right Mouse Button pressed at: (" << mousePos.x << ", " << mousePos.y << ")" << endl;
            }

            bool menu = !options_ && !play && !view_dif && !lose && !resume;

            // Menu Logic
            if (menu) 
            {
                gamemenu.bt_clicks(window, event, options_, play);

                if (play) 
                {
                    gameplay.resetGame();    // Reset tank positions
                    gameplay.resetScore();   // Reset score, lives, and level
                    gameOver = false;
                }

                gamemenu.MilataryView(event, view_dif);
            }

            // Options Page
            if (options_) 
            {
                resumepage.sound_play();
                lostpage.stop_sound();
                gamemenu.stop_sounds();
                options.back_menu(event, options_);
            }

            // Game Logic
            if (play) 
            {

                lostSoundPlayed = false;

                resumepage.sound_stop();
                lostpage.stop_sound();
                gamemenu.stop_sounds();
                gameplay.play_bg();

                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) 
                {
                    gameplay.button_sound();
                    play = false;            // Exit to Resume Page
                    resume = true;
                }

                gameplay.movement(event);
                gameplay.bullet1(event);
            }

            // Lost Condition
            if (lose) 
            {
                lostpage.handle_buttons(window, play, lose, menu, gameplay);
            }

            // Resume Page
            if (resume) 
            {

                gamemenu.stop_sounds();
                gameplay.stop_bg();

                resumepage.sound_play();

                resumepage.handle_buttons(window, play, resume, menu, gameplay);
            }
            
            // Veiwer Page
            if (view_dif) 
            {

                gamemenu.stop_sounds();
                gameplay.stop_bg();

                resumepage.sound_play();

                tankveiwer.handleInput(window, view_dif);

            }

            
        }

        // Rendering

        window.clear();

        if (!options_ && !play && !lose && !resume && !view_dif) 
        {

            lostSoundPlayed = false;

            resumepage.sound_stop();
            gameplay.stop_bg();
            gamemenu.song();

            gamemenu.draw_bg(window);
            gamemenu.draw_others(window);
            gamemenu.draw(window);
        }

        else if (options_) 
        {
            options.draw(window);
        }

        else if (play)
        {
            float deltaTime = cloak.restart().asSeconds();

            gameplay.enemy_tank1(event, window); 
            gameplay.draw_stuff(window);          
            gameplay.bullet2(window);             
            gameplay.checkBulletColision(window, play, lose);

            gameplay.explode(deltaTime);          
            gameplay.draw_explode(window);
        }


        else if (lose) 
        {
            resumepage.sound_stop();
            gamemenu.stop_sounds();
            gameplay.stop_bg();

            if (!lostSoundPlayed) 
            {
                lostpage.play_sound();
                lostSoundPlayed = true;  // Ensure sound is played only once
            }

            lostpage.render(window);
        }

        else if (resume) 
        {
            resumepage.render(window);
        }

        else if (view_dif)
        {
            tankveiwer.render(window);
        }

        window.display();
    }

    return 0;
}