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

sf::Font global_font;

using namespace std;


int main()
{


#pragma region Sql


	// open database

	const char* dateiname = "Snake_Highscores.sqlite";

	ifstream dateistrom(dateiname);

	if (!dateistrom.good()) {
		cout << "Datei kann nicht geöffnet werden" << endl;
	}
	else {

		// create object for database
		sqlite3* datenbank;

		try {
			sqlite3_open(dateiname, &datenbank);

			

			const char* sqlSelectString = "SELECT * FROM Highscores"; 

			char* fehlermeldung;

			// prepare object for result
			char ** ergebnisse = NULL;
			int anzahlSpalten;
			int anzahlZeilen;

			int fehlercode = sqlite3_get_table(datenbank, sqlSelectString, &ergebnisse, &anzahlZeilen, &anzahlSpalten, &fehlermeldung);

			int fehlercode2 = sqlite3_exec(datenbank, "INSERT INTO..", NULL, NULL, &fehlermeldung);

			// if an error occured
			if (fehlercode != 0) {
				cout << "Error: " << fehlermeldung << endl;
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


	// start RNG with actual time
	srand(time(0));


	try
	{
		global_font.loadFromFile("arial.ttf");
	}
	catch (exception& ex)
	{

	}

	// create the main window with its dimension and its title
	sf::RenderWindow window(sf::VideoMode(GAMESIZE_X, GAMESIZE_Y), "Snake Game using SFML!");


	const float FPS = 8.0f; //The desired FPS. (The number of updates each second).
	window.setFramerateLimit(FPS);

	// create a lvl object
	Level lvl1(&global_font);

	// 
	lvl1.readHighScoresFromFile();

	lvl1.currentHighscoreScore = stoi(lvl1.fileContent[0]);
	lvl1.currentHighscoreDate = lvl1.fileContent[1];


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

		// Wait for keypress of the S Key
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !lvl1.gameRunning)
		{
			lvl1.gameRunning = true;
			lvl1.gameOver = false;
			lvl1.createBoundaries();
			lvl1.clock.restart();
		}

		// Wait for keypress of the Q Key
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
				lvl1.prepareStats();

				window.clear();

				//lvl1.checkNewHighscore();

				if (lvl1.score > lvl1.currentHighscoreScore)
				{
					lvl1.currentHighscoreScore = lvl1.score;
					lvl1.currentHighscoreDate = lvl1.dayString + "." + lvl1.monthString + "." + lvl1.yearString + " at " + lvl1.hourString + ":" + lvl1.minuteString;
					window.draw(lvl1.txt_newHighScoreAchieved);
				}



				lvl1.writeHighScoresToFile();

				

				// Draw the boundaries that limit the map
				for (int i = 0; i < lvl1.boundaries.size(); i++)
				{
					window.draw(lvl1.boundaries[i]);
				}

				window.draw(lvl1.txt_gameOver);
				window.draw(lvl1.txt_playtimeFood);
				window.draw(lvl1.txt_totalScore);
				window.draw(lvl1.txt_date);
				window.draw(lvl1.txt_instrcution3);
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

				// Get start values
				lvl1 = Level(&global_font);

				lvl1.readHighScoresFromFile();
			
				lvl1.currentHighscoreScore = stoi(lvl1.fileContent[0]);
				lvl1.currentHighscoreDate = lvl1.fileContent[1];

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

			window.draw(lvl1.txt_instrcution);
			window.draw(lvl1.txt_instrcution2);
			window.display();
		}
	}

	return 0;
}