#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <string>

using namespace std;
using namespace sf;

class DifTank {

    private:

        Texture tankTextures[10];
        RectangleShape currentTank;
        int currentIndex;
        Font font, headingFont;
        Text titleText, tankInfoText;
        RectangleShape frame, infoBox, backButton, background, background2;
        RectangleShape navBoxes[9];

        SoundBuffer bt1;
        Sound bt;

        Text backText;


        struct TankData {
            string name;
            string info;
        };

        TankData tanks[9] = 
        {
            {"Al-Khalid", "Country: Pakistan\nRole: Main Battle Tank\nWeight: 46 tonnes\nCrew: 3\nSpeed: 72 km/h\nMain Gun: 125 mm"},
            {"M1 Abrams", "Country: USA\nRole: Main Battle Tank\nWeight: 67.6 tonnes\nCrew: 4\nSpeed: 72 km/h\nMain Gun: 120 mm"},
            {"T-14 Armata", "Country: Russia\nRole: Main Battle Tank\nWeight: 48 tonnes\nCrew: 3\nSpeed: 80 km/h\nMain Gun: 125 mm"},
            {"Type 99A", "Country: China\nRole: Main Battle Tank\nWeight: 54 tonnes\nCrew: 3\nSpeed: 80 km/h\nMain Gun: 125 mm"},
            {"Pokpung-ho", "Country: North Korea\nRole: Main Battle Tank\nWeight: 44 tonnes\nCrew: 4\nSpeed: 70 km/h\nMain Gun: 125 mm"},
            {"Leopard 2A7", "Country: Germany\nRole: Main Battle Tank\nWeight: 67.5 tonnes\nCrew: 4\nSpeed: 72 km/h\nMain Gun: 120 mm"},
            {"Arjun Mk1A", "Country: India\nRole: Main Battle Tank\nWeight: 68.6 tonnes\nCrew: 4\nSpeed: 70 km/h\nMain Gun: 120 mm"},
            {"Leclerc", "Country: France\nRole: Main Battle Tank\nWeight: 56 tonnes\nCrew: 3\nSpeed: 71 km/h\nMain Gun: 120 mm"},
            {"Karrar", "Country: Iran\nRole: Main Battle Tank\nWeight: 51 tonnes\nCrew: 3\nSpeed: 65 km/h\nMain Gun: 125 mm"}
        };

    public:

        DifTank() : currentIndex(0) 
        {
            // Load fonts
            font.loadFromFile("game/fonts/font1.ttf");
            headingFont.loadFromFile("game/fonts/font2.ttf");

            bt1.loadFromFile("game/sounds/button_chng.ogg");
            bt.setBuffer(bt1);

            // Setup frame
            frame.setSize(Vector2f(410, 220));
            frame.setFillColor(Color(0, 50, 0, 230));
            frame.setOutlineThickness(2);
            frame.setOutlineColor(Color::White);
            frame.setPosition(20, 100);

            // Current Tank
            currentTank.setSize(Vector2f(410, 220));

            // Setup info box
            infoBox.setSize(Vector2f(440, 220));
            infoBox.setFillColor(Color(0, 50, 0, 230));
            infoBox.setOutlineThickness(2);
            infoBox.setOutlineColor(Color::White);
            infoBox.setPosition(460, 100);

            // Setup title text
            titleText.setFont(headingFont);
            titleText.setString("Tank Viewer");
            titleText.setCharacterSize(50);
            titleText.setFillColor(Color::Green);
            titleText.setPosition(200, 10);
            titleText.setOutlineColor(Color::White);
            titleText.setOutlineThickness(4);

            // Setup tank info text
            tankInfoText.setFont(font);
            tankInfoText.setCharacterSize(18);
            tankInfoText.setFillColor(Color::White);
            tankInfoText.setPosition(infoBox.getPosition().x + 10, infoBox.getPosition().y + 10);

            // Setup navigation boxes
            for (int i = 0; i < 9; ++i) 
            {
                navBoxes[i].setSize(Vector2f(20, 20));
                navBoxes[i].setFillColor(Color(50, 50, 50, 150));
                navBoxes[i].setOutlineThickness(1);
                navBoxes[i].setOutlineColor(Color::White);
                navBoxes[i].setPosition(460 + i * 25, 340);
            }

            // Setup back button
            setupBackButton();

            // Load textures
            loadTextures();
            updateTankDisplay();

            // Background
            background.setSize(Vector2f(800, 400));
            background.setPosition(0, 0);
            background.setTexture(&tankTextures[9]);

            background2.setSize(Vector2f(800, 400));
            background2.setPosition(0, 0);
            background2.setFillColor(Color(0, 0, 0, 150));

            // Back button label
            backText.setFont(font);
            backText.setString("Back");
            backText.setCharacterSize(20);
            backText.setFillColor(Color::White);
            backText.setPosition(backButton.getPosition().x + 25, backButton.getPosition().y + 2);
        }

        void setupBackButton() 
        {
            backButton.setSize(Vector2f(80, 30));
            backButton.setFillColor(Color(0, 100, 0, 150));
            backButton.setOutlineThickness(2);
            backButton.setOutlineColor(Color::White);
            backButton.setPosition(20, 350);
        }

        void loadTextures() 
        {
        
            tankTextures[0].loadFromFile("game/images/dif1.png");
            tankTextures[1].loadFromFile("game/images/dif2.png");
            tankTextures[2].loadFromFile("game/images/dif3.png");
            tankTextures[3].loadFromFile("game/images/dif4.png");
            tankTextures[4].loadFromFile("game/images/dif5.png");
            tankTextures[5].loadFromFile("game/images/dif6.png");
            tankTextures[6].loadFromFile("game/images/dif7.png");
            tankTextures[7].loadFromFile("game/images/dif8.png");
            tankTextures[8].loadFromFile("game/images/dif9.png");

            tankTextures[9].loadFromFile("game/images/menu.png");

        }

        void updateTankDisplay() 
        {

            currentTank.setTexture(&tankTextures[currentIndex]);
            currentTank.setPosition(20, 100);

            // Update tank info text
            string tankInfo = "Tank Name: " + tanks[currentIndex].name + "\n" + tanks[currentIndex].info;
            tankInfoText.setString(tankInfo);

            // Update nav box colors
            for (int i = 0; i < 9; ++i) 
            {
                if (i == currentIndex) 
                {
                    navBoxes[i].setFillColor(Color::White);
                }
                else 
                {
                    navBoxes[i].setFillColor(Color(50, 50, 50, 150));
                }
            }
        }


        void handleInput(RenderWindow& window, bool& view) 
        {
            Vector2i mousePos = Mouse::getPosition(window);

            if (Mouse::isButtonPressed(Mouse::Left)) 
            {
                if (backButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) 
                {
                    bt.play();
                    view = false;
                }

                else 
                {
                    for (int i = 0; i < 9; ++i) 
                    {
                        if (navBoxes[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) 
                        {
                            bt.play();
                            currentIndex = i;
                            updateTankDisplay();
                            break;
                        }
                    }
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::B)) 
            {
                bt.play();
                view = false;
            }

            if (Keyboard::isKeyPressed(Keyboard::Right)) 
            {
                bt.play();
                currentIndex = (currentIndex + 1) % 9;
                updateTankDisplay();
            }

            if (Keyboard::isKeyPressed(Keyboard::Left)) 
            {
                bt.play();
                currentIndex = (currentIndex - 1 + 9) % 9;
                updateTankDisplay();
            }
        }

        void render(RenderWindow& window) 
        {
            window.draw(background);
            window.draw(background2);
            window.draw(frame);
            window.draw(infoBox);
            window.draw(currentTank);
            window.draw(titleText);
            window.draw(tankInfoText);

            for (const auto& navBox : navBoxes) 
            {
                window.draw(navBox);
            }

            window.draw(backButton);
            window.draw(backText);
        }
};