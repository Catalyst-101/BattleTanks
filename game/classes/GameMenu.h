#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

using namespace sf;

#define MAX_NUMBER_OF_ITEMS 3

class GameMenu
{
	public:

		GameMenu();
		~GameMenu();

		void draw_bg(RenderWindow& window);
		void draw(RenderWindow& window);
		void draw_others(RenderWindow& window);

		void song();
		void stop_sounds();

		void MoveUp();
		void MoveDown();
		int GetPressedItem() 
		{
			return selectedItemIndex; 
		}

		void bt_clicks(RenderWindow& window, Event& event, bool& options, bool& play);

		void MilataryView(Event& event, bool& view_dif);

	private:

		bool bg_song = true;
		int selectedItemIndex;
		Font font;
		Text menu[MAX_NUMBER_OF_ITEMS];
		Texture t6;
		Sprite bg;
		Text head, tankveiw_;
		SoundBuffer s1, bt1;
		Sound bg_s, bt;
		RectangleShape box[6];

};