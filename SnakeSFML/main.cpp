//////////////////////////////////////////////////////////////////////////////////////////////
//																							//
//	Author:		DS																			//
//	Created:	2019.06.17																	//
//																							//
//////////////////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <string>
#include <fstream>
#include "sqlite3.h"

#include "level.h"


#define GAMESIZE_X 500
#define GAMESIZE_Y 500

using namespace std;


int main()
{
	// start RNG with actual time
	srand(time(0));

#pragma region Sql


	// öffnen der Datenabnk
	string Name[3];
	string Highscore[3];
	string Date[3];

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

						if (datenposition == 0)
						{
							Name[zeile] = ergebnisse[datenposition];
						}
						else if (datenposition == 1)
						{
							Highscore[zeile] = ergebnisse[datenposition];
						}
						else if (datenposition == 2)
						{
							Date[zeile] = ergebnisse[datenposition];
						}
							

					}

					// Zeilenumbruch nach jeder Zeile
					cout << endl;

				}


			}
			/*
			cout << Name[0] << endl;
			cout << Name[1] << endl;
			cout << Name[2] << endl;
			*/
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
	sf::RenderWindow window(sf::VideoMode(GAMESIZE_X, GAMESIZE_Y), "Snake Game using SFML!");


	const float FPS = 8.0f; //The desired FPS. (The number of updates each second).
	window.setFramerateLimit(FPS);

	// create a lvl object
	Level lvl1;


	// try catch
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		// error...
	}
	

	sf::FloatRect bounds;

	sf::Text instrcution;
	instrcution.setFont(font);
	instrcution.setString("Press s to start or q to quit");
	instrcution.setCharacterSize(24);
	instrcution.setFillColor(sf::Color::Green);
	instrcution.setStyle(sf::Text::Bold);
	bounds = instrcution.getLocalBounds();
	instrcution.setPosition((GAMESIZE_X/2) - (bounds.width / 2), 100);


	sf::Text instrcution2;
	instrcution2.setFont(font);
	instrcution2.setString("Use a for left or d for right to control the snake GLHF");
	instrcution2.setCharacterSize(16);
	instrcution2.setFillColor(sf::Color::Green);
	instrcution2.setStyle(sf::Text::Bold);
	bounds = instrcution2.getLocalBounds();
	instrcution2.setPosition((GAMESIZE_X / 2) - (bounds.width / 2), 450);


	sf::Text instrcution3;
	instrcution3.setFont(font);
	instrcution3.setString("Use b to go back to the menu or q to quit");
	instrcution3.setCharacterSize(16);
	instrcution3.setFillColor(sf::Color::Green);
	instrcution3.setStyle(sf::Text::Bold);
	bounds = instrcution3.getLocalBounds();
	instrcution3.setPosition((GAMESIZE_X / 2) - (bounds.width / 2), 450);






	sf::Text gameOver;
	gameOver.setFont(font);
	gameOver.setString("**** GameOver ****");
	gameOver.setCharacterSize(24);
	gameOver.setFillColor(sf::Color::Red);
	gameOver.setStyle(sf::Text::Bold);
	bounds = gameOver.getLocalBounds();
	gameOver.setPosition((GAMESIZE_X/2) - (bounds.width/2), 100);




	sf::Text playtimeFood;
	playtimeFood.setFont(font);
	playtimeFood.setString("**** playtimefodd ****");
	playtimeFood.setCharacterSize(20);
	playtimeFood.setFillColor(sf::Color::Green);
	playtimeFood.setStyle(sf::Text::Bold);
	

	sf::Text totalScore;
	totalScore.setFont(font);
	totalScore.setString("**** Total Score ****");
	totalScore.setCharacterSize(20);
	totalScore.setFillColor(sf::Color::Green);
	totalScore.setStyle(sf::Text::Bold);


	sf::Text date;
	date.setFont(font);
	date.setString("**** Date ****");
	date.setCharacterSize(20);
	date.setFillColor(sf::Color::Green);
	date.setStyle(sf::Text::Bold);


	// Will be executed as long as the window is open
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


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !lvl1.gameRunning)
		{
			lvl1.gameRunning = true;
			lvl1.gameOver = false;
			lvl1.createBoundaries();
			lvl1.clock.restart();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			window.close();
		}

		// Game Main Loop
		if (!lvl1.gameOver && lvl1.gameRunning)
		{

			// check if food is on field
			if (!lvl1.foodOnField)
			{
				lvl1.generateFood();
				lvl1.foodOnField = true;
			}


			// Wait for keypress of the A Key
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				lvl1.snake.direction -= 1;	// Cycle trough directions counterclockwise
			}


			// Wait for keypress of the D Key
			else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				lvl1.snake.direction += 1;	// Cycle trough directions clockwise
			}
			else
			{
				// Direction remains as it is
			}


			// Check for Direction Overflow
			lvl1.snake.checkDirectionOverflow();


			// Check if snake has found some food and let it grow
			lvl1.checkSnakeAteFood();


			// Update the snake values
			lvl1.snake.updateSnake();

			// Set direction based on user input
			lvl1.snake.setSnakeDirection();



			// Clear the window
			window.clear();

			// Draw the boundaries that limit the map
			for (int i = 0; i < lvl1.boundaries.size(); i++)
			{
				window.draw(lvl1.boundaries[i]);
			}


			// Draw head of the snake
			window.draw(lvl1.snake.head);


			// Draw the body of the snake depending on its size
			for (int i = 0; i < lvl1.snake.snakebody.size(); i++)
			{
				window.draw(lvl1.snake.snakebody[i]);
			}


			// Draw the food
			window.draw(lvl1.food);

			




			// check if GameOver condition is satisfied
			lvl1.checkGameOver();

			if (lvl1.gameOver)
			{
				lvl1.calculateStats();
				//lvl1.showStats();

				string scoreString = to_string(lvl1.score);
				string foodString = to_string(lvl1.foodCount);
				string timeElapsedString = to_string(lvl1.timeElapsed.asSeconds());
				string yearString = to_string(lvl1.year);
				string monthString = to_string(lvl1.month);
				string dayString = to_string(lvl1.day);
				string hourString = to_string(lvl1.hour);
				string minuteString = to_string(lvl1.minute);

				playtimeFood.setString("You lasted " + timeElapsedString + " seconds" + " and ate " + foodString + " food");

				bounds = playtimeFood.getLocalBounds();
				playtimeFood.setPosition((GAMESIZE_X / 2) - (bounds.width / 2), 150);


				totalScore.setString("Your Score: " + scoreString + " Points");

				bounds = totalScore.getLocalBounds();
				totalScore.setPosition((GAMESIZE_X / 2) - (bounds.width / 2), 200);


				date.setString("Played on " + dayString + "." + monthString + "." + yearString + " at " + hourString + ":" + minuteString);
				bounds = date.getLocalBounds();
				date.setPosition((GAMESIZE_X / 2) - (bounds.width / 2), 250);


				window.clear();

				// Draw the boundaries that limit the map
				for (int i = 0; i < lvl1.boundaries.size(); i++)
				{
					window.draw(lvl1.boundaries[i]);
				}


				window.draw(gameOver);
				window.draw(playtimeFood);
				window.draw(totalScore);
				window.draw(date);
				window.draw(instrcution3);
			}

			// displays the items in the window
			window.display();

		}
		// GameOver
		else if (lvl1.gameOver && lvl1.gameRunning)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
			{
				lvl1.gameRunning = false;
				lvl1 = Level();
				//window.clear();
				//window.display();

				//window.close();
				// maybe gamerunning = false
				//lvl1.gameRunning = false;
			}
		}

		else
		{
			lvl1.createBoundaries();

			window.clear();

			// Draw the boundaries that limit the map
			for (int i = 0; i < lvl1.boundaries.size(); i++)
			{
				window.draw(lvl1.boundaries[i]);
			}


			window.draw(instrcution);
			window.draw(instrcution2);


			window.display();
		}

	}

	return 0;
}