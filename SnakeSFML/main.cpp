#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "Snake Game using SFML!");



	sf::CircleShape head(20.f);
	head.setFillColor(sf::Color::Green);
	head.setPosition(0, 0);

	sf::CircleShape body(20.f);
	body.setFillColor(sf::Color::Red);
	body.setPosition(100, 100);


	sf::CircleShape snake[10];
	snake[0].setRadius(20.f);
	

	sf::RectangleShape boundary;
	
	sf::Vector2f test;
	test.x = 20;
	test.y = 20;

	boundary.setSize(test);
	boundary.setPosition(200, 30);
	boundary.setFillColor(sf::Color::Red);

/*
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		// error...
	}
*/

	sf::Text text;

	//text.setFont(font);
	text.setString("GameOver");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	vector<sf::CircleShape> snakebody;
	/*
	
	sf::CircleShape newBodyPart(20.f);
	newBodyPart.setFillColor(sf::Color::Green);
	*/

	int testflag = 0;
	 
	int x = 20;
	int y = 20;

	sf::Time timeTest = sf::seconds(0.25);

	while (window.isOpen())
	{
	


		sf::sleep(timeTest);
		cout << "Loop" << endl;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		// will be executed as long as the button is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{

			head.setFillColor(sf::Color::Green);
			body.setFillColor(sf::Color::Red);

			testflag++;
			
			if (testflag == 1)
			{
				
				sf::CircleShape newBodyPart(20.f);
				newBodyPart.setFillColor(sf::Color::Green);
				newBodyPart.setPosition(x, y);
				snakebody.push_back(newBodyPart);
				x += 20;
				y += 20;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			head.setFillColor(sf::Color::Red);
			body.setFillColor(sf::Color::Green);
			cout << snakebody.size() << endl;
			testflag = 0;

		}


		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			testflag = 0;
		}
		

		sf::CircleShape newBodyPart(20.f);
		newBodyPart.setFillColor(sf::Color::Green);
		newBodyPart.setPosition(x, y);
		snakebody.push_back(newBodyPart);
		x += 20;
		y += 20;


		window.clear();


		window.draw(head);
		window.draw(body);
		window.draw(text);
		window.draw(boundary);


		for (int i = 0; i < snakebody.size(); i++)
		{
			window.draw(snakebody[i]);
		}

		window.display();
	}

	return 0;
}