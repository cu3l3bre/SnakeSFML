//////////////////////////////////////////////////////////////////////////////////////////////
//																							//
//	Author:		DS																			//
//	Created:	2019.06.17																	//
//																							//
//////////////////////////////////////////////////////////////////////////////////////////////


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Clock.hpp>
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



	// create the main window with its dimension and its title
	sf::RenderWindow window(sf::VideoMode(500, 550), "Snake Game using SFML!");


	const float FPS = 8.0f; //The desired FPS. (The number of updates each second).
	window.setFramerateLimit(FPS);

	// create a lvl object
	Level lvl1;


	// create the shape for the snake head
	sf::CircleShape head;
	head.setRadius(5.f);
	head.setFillColor(sf::Color::Red);


	// create the shape for the snake body
	sf::CircleShape body;
	body.setRadius(5.f);
	body.setFillColor(sf::Color::Green);


	// create the shape for the food
	sf::CircleShape food;
	food.setRadius(5.f);
	food.setFillColor(sf::Color::Yellow);


	// create dimensions for one recantangle boundary
	sf::Vector2f rectangleSize;
	rectangleSize.x = 10;
	rectangleSize.y = 10;

	// creathe the object for the rectangle boundary
	sf::RectangleShape boundary;
	boundary.setSize(rectangleSize);
	boundary.setFillColor(sf::Color::Red);
	

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


	// create a vector of circleshapes which represent the snakebody
	vector<sf::CircleShape> snakebody;
	
	// create a vecotor which stores all boundaries around the field
	vector<sf::RectangleShape> boundaries;


	lvl1.clock.restart();
	//sf::Time timelapsed;

	// set the boundaries around the field 
	for (int i = 5; i <= 495; i += 5)
	{
		for (int j = 5; j <= 495; j += 5)
		{
			if((i == 5) || (j == 5) || (i == 495) || (j == 495))
			{

				boundary.setPosition(i-5, j-5);	// set the origin of each boundary
				boundaries.push_back(boundary);
			}
		}
	}


	// will be executed as long as the window is open
	while (window.isOpen())
	{
	
		sf::Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed))
			{
				window.close();
			}
		}

		
		if (!lvl1.gameOver)
		{
			

			// Wait for keypress of the A Key
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				lvl1.snake.direction -= 1;	// cycle trough directions counterclockwise
			}


			// Wait for keypress of the D Key
			else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				lvl1.snake.direction += 1;	// cycle trough directions clockwise
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

			// check if food is on field
			if (!lvl1.foodOnField)
			{
				lvl1.generateFood();
				lvl1.foodOnField = true;
			}



			// check if snake has found some food and let it grow
			if ((lvl1.foodLocation.row == lvl1.snake.snakePoints[0].row) && (lvl1.foodLocation.col == lvl1.snake.snakePoints[0].col))
			{
				lvl1.eatFood();
			}


			// update the snake values
			lvl1.snake.updateSnake();

			// write new point vlaue in 0
			switch (lvl1.snake.direction)
			{
			case SnakeUp: lvl1.snake.snakePoints[0].row -= 10; break;
			case SnakeRight: lvl1.snake.snakePoints[0].col += 10; break;
			case SnakeDown: lvl1.snake.snakePoints[0].row += 10; break;
			case SnakeLeft: lvl1.snake.snakePoints[0].col -= 10; break;
			default:break;
			}




			// Set the drawing origin for the head of the snake 
			// since the head has a radius of 5, we have to -5 the get to the upper left corner
			head.setPosition(lvl1.snake.snakePoints[0].col - 5, lvl1.snake.snakePoints[0].row - 5);


			// Set the drawing location for each body part of the snake 
			for (int i = 1; i < lvl1.snake.snakePoints.size(); i++)
			{
				body.setPosition(lvl1.snake.snakePoints[i].col - 5, lvl1.snake.snakePoints[i].row - 5);
				snakebody.push_back(body);
			}

			// Set the drawing location for the food 
			food.setPosition(lvl1.foodLocation.col - 5, lvl1.foodLocation.row - 5);

			// Draw Items inside the window
			window.clear();

			// Draw the boundaries that limit the map
			for (int i = 0; i < boundaries.size(); i++)
			{
				window.draw(boundaries[i]);
			}

			// Draw head of the snake
			window.draw(head);

			// Draw the body of the snake depending on its size
			for (int i = 0; i < snakebody.size(); i++)
			{
				window.draw(snakebody[i]);
			}

			// Draw the food
			window.draw(food);


			// displays the items in the window
			window.display();


			// clear the vector of after it has been drawn
			snakebody.clear();

			// check if GameOver condition is reached
			lvl1.checkGameOver();

			if (lvl1.gameOver)
			{
				lvl1.calculateStats();
				lvl1.showStats();
			}

		}
		// GameOver
		else
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			{
				window.close();
			}
		}

	}

	return 0;
}