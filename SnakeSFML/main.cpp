//////////////////////////////////////////////////////////////////////////////////////////////
//																							//
//	Author:		DS																			//
//	Created:	2019.06.17																	//
//																							//
//////////////////////////////////////////////////////////////////////////////////////////////


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include "sqlite3.h"

#include "snake.h"
#include "level.h"

#include "time.h"

using namespace std;

int main()
{
	// start RNG with actual time
	srand(time(0));

#pragma region Sql


	// öffnen der Datenabnk


	const char* dateiname = "Snake_Highscores.sqlite";

	ifstream dateistrom(dateiname);

	if (!dateistrom.good()) {
		cout << "Datei kann nicht geöffnet werden" << endl;
	}
	else {

		// Objekt für die Datenbank anlegen
		sqlite3* datenbank;

		try {
			sqlite3_open(dateiname, &datenbank);

			

			const char* sqlSelectString = "SELECT * FROM Highscores"; 

			char* fehlermeldung;

			// Objekt für das Ergebnis vorbreiten
			char ** ergebnisse = NULL;
			int anzahlSpalten;
			int anzahlZeilen;

			int fehlercode = sqlite3_get_table(datenbank, sqlSelectString, &ergebnisse, &anzahlZeilen, &anzahlSpalten, &fehlermeldung);

			int fehlercode2 = sqlite3_exec(datenbank, "INSERT INTO..", NULL, NULL, &fehlermeldung);

			// wenn ein fhler aufgetreten
			if (fehlercode != 0) {
				cout << "Fehler: " << fehlermeldung << endl;
			}
			else {


				//ergebnisse = [0,0][1,0][1,0][1,1][2,0][2,1]

				// eins weiter gehen, um auch die tabellenköpfe mit anzuzeigen
				for (int zeile = 0; zeile <= anzahlZeilen; zeile++) {

					for (int spalte = 0; spalte < anzahlSpalten; spalte++) {

						// Position in der Ergebnisluiste berechene
						int datenposition = (zeile * anzahlSpalten) + spalte;

						cout << ergebnisse[datenposition] << "  ";

					}

					// Zeilenumbruch nach jeder Zeile
					cout << endl;

				}


			}

			//speicher wieder freigeben
			sqlite3_free_table(ergebnisse);

		}
		catch (exception ex) {
			cout << "Verbindung kann nicht geöffnet werden" << endl;
		}


	}

	dateistrom.close();


	// anzeige aller Daten in der tablle highscore

#pragma endregion



	const float FPS = 8.0f; //The desired FPS. (The number of updates each second).

	
	


	sf::RenderWindow window(sf::VideoMode(500, 515), "Snake Game using SFML!");
	window.setFramerateLimit(FPS);

	//Snake lvl1.snake;
	Level lvl1;


	sf::CircleShape head;
	head.setRadius(5.f);
	head.setFillColor(sf::Color::Red);
	head.setPosition(lvl1.snake.location.row, lvl1.snake.location.row);

	
	sf::CircleShape body;
	body.setRadius(5.f);
	body.setFillColor(sf::Color::Red);
	body.setPosition(100, 100);


	sf::CircleShape food;
	food.setRadius(5.f);
	food.setFillColor(sf::Color::Yellow);
	//food.setPosition(100, 100);




	sf::Vector2f rectangleSize;
	rectangleSize.x = 10;
	rectangleSize.y = 10;

	sf::RectangleShape boundary;
	boundary.setSize(rectangleSize);
	boundary.setFillColor(sf::Color::Red);
	boundary.setPosition(100, 100);
	


	sf::CircleShape newBodyPart();
	//sf::CircleShape newBodyPart(20.f);


	/*
	sf::CircleShape snake[10];
	snake[0].setRadius(20.f);
	

	sf::RectangleShape boundary;
	sf::RectangleShape boundary2;
	
	sf::Vector2f test;
	test.x = 10;
	test.y = 10;
	
	int offset = 5;

	int pointx = 5;
	int pointy = 5;

	boundary.setSize(test);
	boundary.setPosition(pointx-offset,pointy-offset);
	boundary.setFillColor(sf::Color::Red);

	boundary2.setSize(test);
	boundary2.setPosition(pointx+10 - offset, pointy - offset);
	boundary2.setFillColor(sf::Color::Green);
	*/
	/*
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		// error...
	}
	*/

	/*
	sf::Text text;

	//text.setFont(font);
	text.setString("GameOver");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	*/

	vector<sf::CircleShape> snakebody;
	vector<sf::RectangleShape> boundaries;

	/*
	
	sf::CircleShape newBodyPart(20.f);
	newBodyPart.setFillColor(sf::Color::Green);
	*/

	int testflag = 0;
	 
	int x = 20;
	int y = 20;

	sf::Time timeTest = sf::seconds(0.25);

	bool DirectionHasBeenSet = false;



	for (int i = 5; i <= 495; i += 5)
	{
		for (int j = 5; j <= 495; j += 5)
		{
			if((i == 5) || (j == 5) || (i == 495) || (j == 495))
			{
				boundary.setPosition(i-5, j-5);
				boundaries.push_back(boundary);
			}
		}
	}

	bool gameOver = false;
	//lvl1.foodOnField = false;

	while (window.isOpen())
	{
	


		//sf::sleep(timeTest);
		//cout << "Loop" << endl;
		DirectionHasBeenSet = false;


		sf::Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed))
			{
				window.close();
			}
		}

		// will be executed as long as the button is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (!DirectionHasBeenSet)
			{
				lvl1.snake.direction -= 1;
				DirectionHasBeenSet = true;
			}
		}

		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (!DirectionHasBeenSet)
			{
				lvl1.snake.direction += 1;
				DirectionHasBeenSet = true;
			}
		}
		else
		{
			// direction remains as it is
		}


		// Check for Overflow
		if (lvl1.snake.direction == -1)
		{
			lvl1.snake.direction = 3;
		}
		else if (lvl1.snake.direction == 4)
		{
			lvl1.snake.direction = 0;
		}
		

		if (!lvl1.foodOnField)
		{
			// limits 15 is possible
			// 485
			lvl1.generateFood();
			lvl1.foodOnField = true;
			//lvl1.foodLocation.col = 485;	// test
			//lvl1.foodLocation.row = 15;
			cout << lvl1.foodLocation.col << endl;	// test
			cout << lvl1.foodLocation.row << endl;	// test
		}



		// Check if snake has found some food and let it grow
		if ((lvl1.foodLocation.row == lvl1.snake.snakePoints[0].row) && (lvl1.foodLocation.col == lvl1.snake.snakePoints[0].col))
		{
			lvl1.eatFood();
			cout << "yum" << endl;
		}



		lvl1.snake.updateSnake();

		// write new point vlaue in 0
		switch (lvl1.snake.direction)
		{
		case SnakeUp: lvl1.snake.snakePoints[0].row -= 10; break;
		case SnakeRight: lvl1.snake.snakePoints[0].col +=10; break;
		case SnakeDown: lvl1.snake.snakePoints[0].row += 10; break;
		case SnakeLeft: lvl1.snake.snakePoints[0].col -=10; break;
		default:break;
		}





		head.setPosition(lvl1.snake.snakePoints[0].col - 5, lvl1.snake.snakePoints[0].row - 5);


		for (int i = 1; i < lvl1.snake.snakePoints.size(); i++)
		{
			body.setRadius(5.f);
			body.setFillColor(sf::Color::Green);
			body.setPosition(lvl1.snake.snakePoints[i].col-5, lvl1.snake.snakePoints[i].row-5);
			snakebody.push_back(body);
		}


		food.setPosition(lvl1.foodLocation.col - 5, lvl1.foodLocation.row - 5);

		// Draw Items inside the window
		window.clear();


		window.draw(head);
		
		/*window.draw(body);
		window.draw(text);
		window.draw(boundary);
		window.draw(boundary2);
		*/

		for (int i = 0; i < snakebody.size(); i++)
		{
			window.draw(snakebody[i]);
		}

		window.draw(food);

		for (int i = 0; i < boundaries.size(); i++)
		{
			window.draw(boundaries[i]);
		}
		
		window.display();

		snakebody.clear();

		gameOver = lvl1.checkGameOver();

		if (gameOver)
		{
			cout << "GameOver" << endl;
			//system("pause");
			window.close();
		}

	}

	return 0;
}