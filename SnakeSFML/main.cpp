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


	// start RNG with actual time
	srand(time(0));


	string pathToHighscoreFile = "Highscores.txt";

	/*
	
	ofstream ausgabeStrom;
	ausgabeStrom.open(pathToHighscoreFile);
	ausgabeStrom << "Hallo das ist ein bla " << endl;
	ausgabeStrom << "hoi hoi hoi " << endl;
	ausgabeStrom << "beep beep beep " << endl;
	ausgabeStrom.close();
	*/


	// Variable vorbereiten, die den ganzen Inhalt der Datei aufnehemen kann
	vector<string> dateiInhalt;

	// gleich ein Objekt mit Übergabe des Dateinamens anlegen
	ifstream eingabeStrom2("Highscores.txt");

	string eineZeile;
	string delimiter = ",";
	string token;
	size_t pos = 0;
	

	while (eingabeStrom2.good()) {

		// Hilfsvaraible vorbereiten
		string eineZeile;

		// lesen einer Zeile
		getline(eingabeStrom2, eineZeile);

		// diese Zeile ans Ende der Liste anfügen
		dateiInhalt.push_back(eineZeile);
	}

	for (int i = 0; i < dateiInhalt.size(); i++)
	{
		cout << "Zeile " << i+1 << ": " << dateiInhalt[i] << endl;
	}

	vector<string> name;
	vector<string> score;
	vector<string> date;



	int test = 0;
	
	
	for (int i = 0; i < dateiInhalt.size(); i++)
	{

		while ((pos = dateiInhalt[i].find(delimiter)) != std::string::npos) {
			token = dateiInhalt[i].substr(0, pos);
			if (test == 0)
			{
				score.push_back(token);
			}
			else if (test == 1)
			{
				name.push_back(token);
			}
			else
			{
				date.push_back(token);
			}


			//std::cout << token << std::endl;
			dateiInhalt[i].erase(0, pos + delimiter.length());
			test++;
		}

		dateiInhalt[i] += "Leer";
		std::cout << dateiInhalt[i] << std::endl;
		test = 0;
	}

	cout << "Score\t" << "Name\t" << "Date" << endl;
	for (int i = 0; i < score.size(); i++)
	{
		
		cout << score[i] << "\t" << name[i] << "\t" << date[i] << endl;
	}

	int testscore = std::stoi(score[0]);
	cout << "Test : " << testscore << endl;


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


				int newHighscore = testscore;

				if (lvl1.score > testscore)
				{
					int newHighscore = lvl1.score;
				}



				window.clear();

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