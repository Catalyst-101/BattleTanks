#pragma once

#include"SFML/Graphics.hpp"
#include"SFML/Audio.hpp"

using namespace sf;

class Options
{
	public:
		
		Options(float width, float height)
		{
			background.loadFromFile("game/images/menu.png");
			keyboard.loadFromFile("game/images/keyboard.png");

			bt1.loadFromFile("game/sounds/button_chng.ogg");
			bt.setBuffer(bt1);

			bg.setSize(Vector2f(width, height));
			bg.setPosition(0, 0);
			bg.setTexture(&background);
			
			info_box.setTexture(&keyboard);
			info_box.setPosition(400, 170);
			info_box.setSize(Vector2f(700, 250));
			info_box.setOrigin(350, 125);
			info_box.setOutlineColor(Color::Black);
			info_box.setOutlineThickness(3);

			back_bt.setFillColor(Color(0, 0, 0, 150));
			back_bt.setPosition(400, 350);
			back_bt.setSize(Vector2f(100, 50));
			back_bt.setOrigin(50, 25);
			back_bt.setOutlineColor(Color::Black);
			back_bt.setOutlineThickness(3);

			font.loadFromFile("game/fonts/font1.ttf");

			text1.setFont(font);
			text1.setString("B A C K");
			text1.setFillColor(Color::White);
			text1.setOutlineColor(Color::Green);
			text1.setOutlineThickness(2);
			text1.setPosition(Vector2f(365, 332));
		}

		void draw(RenderWindow& window)
		{
			window.draw(bg);
			window.draw(info_box);
			window.draw(back_bt);
			window.draw(text1);
		}

		void back_menu(Event& event, bool &options)
		{
			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
			{
				if (back_bt.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					bt.play();
					options = false;
				}
			}

			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::B)
			{
				bt.play();
				options = false;
			}
		}

	private:
	
		RectangleShape bg, info_box, back_bt;
		Font font;
		Text text1;

		Texture background, keyboard;

		SoundBuffer bt1;
		Sound bt;

};