#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
	int randHold;
	int xHold;
	int yHold;


	int pointCount = 3;
	/*bool pointsGen = true;
	
	cout << "How many points would you like?" << endl;
	cin >> pointCount;*/


	
	
	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);
	
	vector<Vector2f> vertices;
	vector<Vector2f> points;


	Text text;

	// select the font
	Font font;
	font.loadFromFile("EuropeanTypewriter.ttf");

	text.setFont(font); // font is a sf::Font

	// set the string to display
	text.setString("Click on any three points on the screen to create the vertices for the triangle.");

	// set the character size
	text.setCharacterSize(24); // in pixels, not points!

	// set the color
	text.setFillColor(sf::Color::White);

	// set the text style
	text.setStyle(Text::Bold | Text::Underlined);
	


	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				// Quit the game when the window is closed
				window.close();
			}


			if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					cout << "the left button was pressed" << endl;
					cout << "mouse x: " << event.mouseButton.x << endl;
					cout << "mouse y: " << event.mouseButton.y << endl;

					if (vertices.size() < 3)
					{
						vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
						
					}
					else if (points.size() == 0)
					{
						///fourth click
						///push back to points vector
						points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));

						
					}
				}
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		****************************************
		Update
		****************************************
		*/

		if (points.size() > 0)// && pointsGen)
		{
			///generate more point(s)
			for (int i = 0; i < pointCount; i++) {
				///select random vertex
				randHold = rand() % 3;

				///calculate midpoint between random vertex and the last point in the vector
				xHold = (vertices[randHold].x + points[points.size() - 1].x) / 2;
				yHold = (vertices[randHold].y + points[points.size() - 1].y) / 2;
				///push back the newly generated coord.
				points.push_back(Vector2f(xHold, yHold));
			}
			//pointsGen = false;
		}

		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();
		
		if (vertices.size() < 3) {
			window.draw(text);
		}
		else if (points.size() == 0) {
			text.setString("Click on a fourth point to start the algorithm.");
			window.draw(text);
		}
		
		for (int i = 0; i < vertices.size(); i++)
		{
			RectangleShape rect(Vector2f(10, 10));
			rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
			rect.setFillColor(Color::White);
			window.draw(rect);
		}
		///TODO:  Draw points
		for (int i = 0; i < points.size(); i++) {
			RectangleShape rect(Vector2f(10, 10));
			rect.setPosition(Vector2f(points[i].x, points[i].y));
			rect.setFillColor(Color::Red);
			window.draw(rect);
			
		}
		

		window.display();
	}
}