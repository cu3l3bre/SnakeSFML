//**************************************************************************************************
/*!
 @file           main.cpp
 @brief          Main programm for the snake game
 @date           17.06.2019
 @author         Daniel Schmunkamp
 */
 //**************************************************************************************************


#include <iostream>
#include <string>
#include <fstream>
#include "sqlite3.h"
#include "level.h"

sf::Font global_font;

using namespace std;

//--------------------------------------------------------------------------------------------------
//! @brief     	Main Function of the snake game application
//--------------------------------------------------------------------------------------------------
int main()
{

#pragma region Sql

	// Open database
	const char* filename = "Snake_Highscores.sqlite";

	ifstream filestream(filename);

	if (!filestream.good()) {
		cout << "File cannont be opened" << endl;
	}
	else {

		// Create object for database
		sqlite3* database;

		try {
			sqlite3_open(filename, &database);

			const char* sqlSelectString = "SELECT * FROM Highscores"; 
			char* errormessage;

			// Prepare object for result
			char ** results = NULL;
			int numberCols;
			int numberRows;

			int errorcode = sqlite3_get_table(database, sqlSelectString, &results, &numberRows, &numberCols, &errormessage);
			int errorcode2 = sqlite3_exec(database, "INSERT INTO..", NULL, NULL, &errormessage);

			// If an error occured
			if (errorcode != 0) {
				cout << "Error: " << errormessage << endl;
			}
			else {

				//results = [0,0][1,0][1,0][1,1][2,0][2,1]

				// Do one more to get the head(description) of the list and to show them
				for (int row = 0; row <= numberRows; row++) {

					for (int col = 0; col < numberCols; col++) {

						// Calculate the postion in the results list
						int dataposition = (row * numberCols) + col;
						cout << results[dataposition] << "  ";
					}
					cout << endl;
				}
			}
			cout << endl;

			// Free memory
			sqlite3_free_table(results);
		}
		catch (exception ex)
		{
			cout << "Connection cannot be opened" << endl;
		}
	}
	filestream.close();

#pragma endregion


	//Check if the font is there
	// if not, do not start the game; it would run, but there are no texts
	if (!global_font.loadFromFile("arial.ttf"))
	{
		cout << "Could not find file arial.ttf" << endl;
		cout << "Please make sure this file is inside the application folder and try again" << endl << endl;
		system("pause");
	}
	// Start the game
	else
	{
		// start RNG with actual time
		srand(time(0));

		// create the main window with its dimension and its title
		sf::RenderWindow window(sf::VideoMode(GAMESIZE_XY, GAMESIZE_XY), "Snake Game using SFML!");

		// Frames per seconds (the number of updates each second)
		const float FPS = 9.0f;
		window.setFramerateLimit(FPS);

		// create a lvl object with the font as param
		Level lvl1(&global_font);

		// Read current highscore from file
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

			// Starts the game
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !lvl1.gameRunning)
			{
				
				lvl1.gameRunning = true;
				lvl1.gameOver = false;
				lvl1.createBoundaries();
				lvl1.clock.restart();
			}

			// Quits the game
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


				// Turn the snake left
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					lvl1.snake.direction -= 1;	// Cycle trough directions counterclockwise
				}


				// Turn the snake right
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

				// Update the snake values, copy them before getting a new one
				lvl1.snake.updateSnake();

				// Set direction based on user input and get new value for the head
				lvl1.snake.setSnakeDirection();
		
				// Check if snake has found some food and let it grow
				lvl1.checkSnakeAteFood();

				//check if GameOver condition is satisfied
				lvl1.checkGameOver();



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


				if (lvl1.gameOver)
				{
					window.clear();

					lvl1.calculateStats();
					lvl1.prepareStats();

					// Check if a new highscore has been achieved
					if (lvl1.score > lvl1.currentHighscoreScore)
					{
						// Get achieved stats
						lvl1.currentHighscoreScore = lvl1.score;
						lvl1.currentHighscoreDate = lvl1.dayString + "." + lvl1.monthString + "." + lvl1.yearString + " at " + lvl1.hourString + ":" + lvl1.minuteString;
						window.draw(lvl1.txt_newHighScoreAchieved);
					}

					// Write highscore to file
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

				// Displays the items in the window
				window.display();

			}
			// GameOver
			else if (lvl1.gameOver && lvl1.gameRunning)
			{
				// Go back to the start menu
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
				{
					
					// Init with start values
					lvl1 = Level(&global_font);

					lvl1.readHighScoresFromFile();

					lvl1.currentHighscoreScore = stoi(lvl1.fileContent[0]);
					lvl1.currentHighscoreDate = lvl1.fileContent[1];
				}
			}

			else
			{
				lvl1.createBoundaries();
				lvl1.prepareCurrentHighscore();

				window.clear();

				// Draw the boundaries that limit the map
				for (int i = 0; i < lvl1.boundaries.size(); i++)
				{
					window.draw(lvl1.boundaries[i]);
				}

				window.draw(lvl1.txt_instrcution);
				window.draw(lvl1.txt_instrcution2);

				window.draw(lvl1.txt_currentHighScoreScore);
				window.draw(lvl1.txt_currentHighScoreDate);

				window.display();
			}
		}
	}
	return 0;
}