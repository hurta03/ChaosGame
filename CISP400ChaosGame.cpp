// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;


int main()
{
	//Load Resources
	sf::Font font;
	if (!font.loadFromFile("fonts/KOMIKAP_.ttf"))
		{
			cout << "Failed" << endl;
		//font.loadFromFile("KOMIKAP.tff");
		}
	//Temp coords class
	class Coord
	{
	public:
		Coord() { x = 0; y = 0; };
		void setCoords(float x, float y){
			this->x = x; this->y = y;};
		float getCoord(char c) {
			if (c == 'x') {return x;}
			else if (c == 'y') { return y; }
			else {return 0;} }

	private:
		float x;
		float y;
	};
	
	//Vector
	sf::Vector2f v1(0.0f, 0.0f);


	//Definitions
	//sf::RectangleShape *dot = new sf::RectangleShape;
	srand(0);

	sf::RectangleShape rectangle;
	vector <sf::RectangleShape> vecRectangles;
	vector <sf::Vector2f> verts;

	Coord clickPoint[4];	//Error when set size to 3

	Coord sim;
	int points = 0;
	bool triExists = false;
	

	// Create a video mode object
	VideoMode vm(1920, 1080);

	Texture textureBackground;
	textureBackground.loadFromFile("");

	Sprite spriteBackground;

	// Attach the texture to the sprite
	spriteBackground.setTexture(textureBackground);

	// Set the spriteBackground to cover the screen
	spriteBackground.setPosition(0, 0);
	spriteBackground.setScale(2,1.3);

	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game", Style::Default);



	while (window.isOpen())
	{

		/*
		****************************************
		Handle the players input
		****************************************
		*/

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
			for (Coord c : clickPoint)
			{
				cout << c.getCoord('x') << endl;
				cout << c.getCoord('y') << endl;
			}
		}
		//test
		//Coord clickCoord;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (points <= 3)
				{
					clickPoint[points].setCoords(event.mouseButton.x, event.mouseButton.y);
					cout << "Click event" << endl;
					cout << "X: " << clickPoint[points].getCoord('x') << " "
						 << "Y: " << clickPoint[points].getCoord('y') << endl;
					rectangle.setSize(sf::Vector2f(10, 10));
					//rectangle.setOutlineColor(sf::Color::White);
					//rectangle.setOutlineThickness(2);
					rectangle.setPosition(clickPoint[points].getCoord('x'), clickPoint[points].getCoord('y'));
					vecRectangles.push_back(rectangle);
					Vector2f xy = rectangle.getPosition();
					cout << "Saved Coord: " << xy.x << " " << xy.y << endl;
					points++;
				}
				
			}
		}
		//Generate pattern
		int maxPoints = 5000;
		if (points > 3 && points < maxPoints)
		{
			cout << "Entering loop " << endl;
			//    return std::rand() % (Max + 1 - Min) + Min;
			int randR = rand() % (255 + 1);
			int randG = rand() % (255 + 1);
			int randB = rand() % (255 + 1);
			//Print number of points for triangle
			for (int i = 2; i < 100; i++)
			{
				int fromThree = rand() % +3;
				float nx = (vecRectangles.at(fromThree).getPosition().x + vecRectangles.back().getPosition().x) / 2;
				float ny = (vecRectangles.at(fromThree).getPosition().y + vecRectangles.back().getPosition().y) / 2;

				rectangle.setSize(sf::Vector2f(2.5, 2.5));
				//rectangle.setOutlineColor(sf::Color::Color(randR, randG, randB));
				rectangle.setFillColor(sf::Color::Color(randR, randG, randB));
				//rectangle.setOutlineThickness(1);
				rectangle.setPosition(nx, ny);
				vecRectangles.push_back(rectangle);
				cout << "Plotting: " << points << endl;
				points++;

			}
		}



		/*
		****************************************
		Update the scene
		****************************************
		*/
		sf::Text text;
		text.setFont(font);
		if (points < 3)
			text.setString("Chaos Game - Select three points to draw the triangle");
		else
			text.setString("Select the fourth point to start the algorithm");
		text.setCharacterSize(30);
		text.setFillColor(sf::Color::White);
		text.setStyle(sf::Text::Bold | sf::Text::Underlined);



		/*
		****************************************
		Draw the scene
		****************************************
		*/

		// Clear everything from the last frame
		window.clear();

		// Draw our game scene here
		window.draw(spriteBackground);

		for (int i = 0; i < vecRectangles.size(); i++)
		{
			window.draw(vecRectangles.at(i));
		}
		window.draw(text);
		// Show everything we just drew
		window.display();


	}

	return 0;
}
