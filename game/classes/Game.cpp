//#include "Game.h"
//#include "SFML/Audio.hpp"
//#include "SFML/Graphics.hpp"
//
//#include<iostream>
//#include<ctime>
//#include<string>
//#include<cstring>
//
//using namespace sf;
//using namespace std;
//
//Game::Game(float window_width, float window_height)
//{
//
//	tank1.setPosition(320, 70);
//	tank2.setPosition(320, 320);
//	tank3.setPosition(720, 320);
//	tank4.setPosition(720, 70);
//	//tank5.setPosition(300, 250);
//
//
//	// Font, texture and sound -->
//	
//	Load_t_s();
//
//	// Background -->
//
//	background.setSize(Vector2f(window_width - 5, window_height - 5));
//	background.setFillColor(Color(0, 0, 0, 0));
//	background.setPosition(4, 3);
//	background.setOutlineColor(Color::Black);
//	background.setOutlineThickness(3);
//
//	// Info Box -->
//
//	info_box.setSize(Vector2f(245, 395));
//	info_box.setFillColor(Color(5, 153, 33, 180));
//	info_box.setPosition(4, 3);
//	info_box.setOutlineColor(Color::Black);
//	info_box.setOutlineThickness(3);
//
//	ScoreBox.setSize(Vector2f(230, 60));
//	ScoreBox.setFillColor(Color(5, 100, 20));
//	ScoreBox.setPosition(12, 12);
//	ScoreBox.setOutlineColor(Color::Black);
//	ScoreBox.setOutlineThickness(2);
//
//	LiveBox.setSize(Vector2f(230, 60));
//	LiveBox.setFillColor(Color(5, 100, 20));
//	LiveBox.setPosition(12, 330);
//	LiveBox.setOutlineColor(Color::Black);
//	LiveBox.setOutlineThickness(2);
//
//	LevelBox.setSize(Vector2f(230, 60));
//	LevelBox.setFillColor(Color(5, 100, 20));
//	LevelBox.setPosition(12, 260);
//	LevelBox.setOutlineColor(Color::Black);
//	LevelBox.setOutlineThickness(2);
//
//	behind_info.setSize(Vector2f(245, 395));
//	behind_info.setTexture(&t3);
//	behind_info.setPosition(4, 3);
//
//	// Battleground -->
//
//	battleground.setTexture(t1);
//	battleground.setPosition(251, 2);
//	battleground.setScale(0.5f, 0.6f);
//
//	// Score, Lives, Level (TEXT) -->
//
//	Score.setString("Score : ");
//	Score.setFont(font);
//	Score.setCharacterSize(50);
//	Score.setPosition(26, 10);
//	Score.setFillColor(Color::White);
//	Score.setOutlineColor(Color::Black);
//	Score.setOutlineThickness(2);
//
//	Live.setString("Lives : ");
//	Live.setFont(font);
//	Live.setCharacterSize(50);
//	Live.setPosition(26, 328);
//	Live.setFillColor(Color::White);
//	Live.setOutlineColor(Color::Black);
//	Live.setOutlineThickness(2);
//
//	Level.setString("Round : ");
//	Level.setFont(font);
//	Level.setCharacterSize(50);
//	Level.setPosition(26, 258);
//	Level.setFillColor(Color::White);
//	Level.setOutlineColor(Color::Black);
//	Level.setOutlineThickness(2);
//}
//
//void Game::Load_t_s()
//{
//	font.loadFromFile("font1.ttf");
//
//	t1.loadFromFile("battleground.png");
//	t2.loadFromFile("wall.png");
//	t3.loadFromFile("infobox_bg.png");
//	t4.loadFromFile("groundbrick.png");
//	t6.loadFromFile("enemy.png");
//
//	s1.loadFromFile("s1.ogg");
//
//	tank_s1.setBuffer(s1);
//}
//
//void Game::draw(RenderWindow& window)
//{
//	// Draw Game Components -->
//	window.draw(battleground);
//	window.draw(background);
//
//	walls.draw(window);
//
//	window.draw(behind_info);
//	window.draw(info_box);
//	window.draw(ScoreBox);
//	window.draw(LiveBox);
//	window.draw(LevelBox);
//	window.draw(Score);
//	window.draw(Live);
//	window.draw(Level);
//}
//
//void Game::draw_tanks(RenderWindow& window)
//{
//	my_tank.print_tank(window);
//
//	tank1.draw(window);
//	tank2.draw(window);
//	tank3.draw(window);
//	tank4.draw(window);
//	//tank5.draw(window);
//}
//
//
//void Game::endgame(RenderWindow& window)
//{
//	window.close();
//}
//
//void Game::movement(Event& gameevent)
//{
//	FloatRect playerBounds = my_tank.my_tank.getGlobalBounds(); // Get the current tank bounds
//
//	my_tank.handleInput(gameevent, walls.checkCollision(playerBounds));
//
//}
//
//// Inside Game's movement method
//void Game::enemy_tank1(Event& event, RenderWindow& window)
//{
//	// Handle bullet updates for tanks
//	tank1.update_bullets(walls, window);
//	tank2.update_bullets(walls, window);
//	tank3.update_bullets(walls, window);
//	tank4.update_bullets(walls, window);
//
//	// Call for each tank to move and fire bullets if needed
//	tank1.moveTank(walls, event, window);
//	tank2.moveTank(walls, event, window);
//	tank3.moveTank(walls, event, window);
//	tank4.moveTank(walls, event, window);
//
//
//}
//
