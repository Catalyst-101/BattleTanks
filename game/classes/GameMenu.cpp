#include"GameMenu.h"
#include"SFML/Audio.hpp"
#include<iostream>

using namespace std;

GameMenu::GameMenu()
{
	font.loadFromFile("font2.ttf");
	bt1.loadFromFile("button_chng.ogg");

	bt.setBuffer(bt1);

	menu[0].setFont(font);
	menu[0].setFillColor(Color::Red);
	menu[0].setString("Play");
	menu[0].setPosition(Vector2f(360, 160));

	menu[1].setFont(font);
	menu[1].setFillColor(Color::White);
	menu[1].setString("Options");
	menu[1].setPosition(Vector2f(325, 240));

	menu[2].setFont(font);
	menu[2].setFillColor(Color::White);
	menu[2].setString("Exit");
	menu[2].setPosition(Vector2f(360, 320));

	selectedItemIndex = 0;

	// For Background Texture -->

	t6.loadFromFile("menu2.png");

	bg.setTexture(t6);
	bg.setPosition(0, 0);
	bg.setScale(0.45f, 0.5f);

	// Head -->

	head.setFont(font);
	head.setString("BattleTanks");
	head.setCharacterSize(70);
	head.setFillColor(Color::Green);
	head.setOutlineColor(Color::Black);
	head.setOutlineThickness(3);
	head.setPosition(Vector2f(130, 35));

	// Boxes -->

	// Other Box-->

	for (int i = 1; i < 4; i++)
	{
		box[i].setSize(Vector2f(300, 50));
		box[i].setPosition(400, 100 + (80 * i));
		box[i].setFillColor(Color(0, 100, 0, 150));
		box[i].setOutlineColor(Color::Black);
		box[i].setOutlineThickness(3);
		box[i].setOrigin(150, 25);
	}

	// Veiw Box -->

	box[5].setSize(Vector2f(100, 40));
	box[5].setPosition(680, 350);
	box[5].setFillColor(Color(0, 100, 0, 150));
	box[5].setOutlineColor(Color::Black);
	box[5].setOutlineThickness(3);

	tankveiw_.setFont(font);
	tankveiw_.setString(" Tank\nViewer");
	tankveiw_.setCharacterSize(12);
	tankveiw_.setFillColor(Color::White);
	tankveiw_.setOutlineColor(Color::Black);
	tankveiw_.setOutlineThickness(2);
	tankveiw_.setPosition(box[5].getPosition().x + 23, box[5].getPosition().y + 5);

	// Sounds -->
	s1.loadFromFile("resume.ogg");

	bg_s.setBuffer(s1);
	bg_s.setVolume(60);


}

void GameMenu::stop_sounds()
{
	bg_s.stop();
}

void GameMenu::song()
{
	if (bg_song && bg_s.getStatus() != Music::Playing)
		bg_s.play();
}

void GameMenu::MilataryView(Event& event, bool& view_dif)
{
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
		if (box[5].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
		{
			bt.play();
			view_dif = true;
		}
}

GameMenu::~GameMenu()
{
}

void GameMenu::draw_others(RenderWindow& window)
{
	for (int i = 1; i < 4; i++)
		window.draw(box[i]);

	window.draw(head);
	window.draw(box[5]);
	window.draw(tankveiw_);

}

void GameMenu::draw(RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void GameMenu::draw_bg(RenderWindow& window)
{
	window.draw(bg);
}

void GameMenu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		bt.play();
		menu[selectedItemIndex].setFillColor(Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(Color::Red);
	}
}

void GameMenu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		bt.play();
		menu[selectedItemIndex].setFillColor(Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(Color::Red);
	}
}

void GameMenu::bt_clicks(RenderWindow& window, Event& event, bool& options, bool& play)
{
	if (event.type == Event::KeyPressed)
	{
		if (event.key.code == Keyboard::Up)
			MoveUp();
		else if (event.key.code == Keyboard::Down)
			MoveDown();

		if (event.key.code == Keyboard::Return)
		{
			switch (GetPressedItem())
			{
			case 0:
				bt.play();
				cout << "The game starts" << endl;
				play = true;
				options = false; // Start the game
				break;
			case 1:
				bt.play();
				cout << "Option button has been pressed" << endl;
				options = true; 
				play = false; // Open the Options Page
				break;
			case 3:
				bt.play();
				window.close();
				break;
			}
		}

	}

	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
		if (box[1].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
		{
			bt.play();
			menu[0].setFillColor(Color::Red);
			menu[selectedItemIndex].setFillColor(Color::White);
			selectedItemIndex = 0;

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
				if (box[1].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					play = true;
		}
		else if (box[2].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
		{
			bt.play();
			menu[1].setFillColor(Color::Red);
			menu[selectedItemIndex].setFillColor(Color::White);
			selectedItemIndex = 1;

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
				if (box[2].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					options = true;
		}
		else if (box[3].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
		{
			bt.play();
			menu[2].setFillColor(Color::Red);
			menu[selectedItemIndex].setFillColor(Color::White);
			selectedItemIndex = 2;

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
				if (box[3].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					window.close();

		}
}