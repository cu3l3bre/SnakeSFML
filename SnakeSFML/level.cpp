//**************************************************************************************************
/*!
 @file           level.cpp
 @brief          Methods for Level class
 @date           17.06.2019
 @author         Daniel Schmunkamp
 */
 //**************************************************************************************************

#include "level.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;


//--------------------------------------------------------------------------------------------------
//! @brief     	Constructor of Level class
//--------------------------------------------------------------------------------------------------
Level::Level()
{
}

//--------------------------------------------------------------------------------------------------
//! @brief     	Constructor of Level class with fonts as param
//--------------------------------------------------------------------------------------------------
Level::Level(sf::Font* newFont)
{
	// Set params for drawing stuff depending on the stepsize
	circleRadius = STEPSIZE / 2;
	stepSize = STEPSIZE;
	offsetOrigin = STEPSIZE / 2;

	// Set path to highscore file (located where the main.cpp is)
	pathToHighscoreFile = "Highsscores.txt";

	// Set some inital values
	gameRunning = false;
	gameOver = false;
	foodOnField = false;
	foodCount = 0;
	score = 0;

	// Set the size for a rectangle
	rectangleSize.x = stepSize;
	rectangleSize.y = stepSize;

	// Set params for one boundary shape
	boundary.setSize(rectangleSize);
	boundary.setFillColor(sf::Color::Red);

	// Set params for the food shape
	food.setRadius(circleRadius);
	food.setFillColor(sf::Color::Yellow);

	// Set params for diffenrent texts
	txt_instrcution.setFont(*newFont);
	txt_instrcution.setString("Press [s] to start or [q] to quit");
	txt_instrcution.setCharacterSize(24);
	txt_instrcution.setFillColor(sf::Color::Green);
	txt_instrcution.setStyle(sf::Text::Bold);
	bounds = txt_instrcution.getLocalBounds();
	txt_instrcution.setPosition((GAMESIZE_XY / 2) - (bounds.width / 2), 100);

	txt_instrcution2.setFont(*newFont);
	txt_instrcution2.setString("Use [a] for left or [d] for right to control the snake GLHF");
	txt_instrcution2.setCharacterSize(16);
	txt_instrcution2.setFillColor(sf::Color::Green);
	txt_instrcution2.setStyle(sf::Text::Bold);
	bounds = txt_instrcution2.getLocalBounds();
	txt_instrcution2.setPosition((GAMESIZE_XY / 2) - (bounds.width / 2), 450);

	txt_instrcution3.setFont(*newFont);
	txt_instrcution3.setString("Use [b] to go back to the menu or [q] to quit");
	txt_instrcution3.setCharacterSize(16);
	txt_instrcution3.setFillColor(sf::Color::Green);
	txt_instrcution3.setStyle(sf::Text::Bold);
	bounds = txt_instrcution3.getLocalBounds();
	txt_instrcution3.setPosition((GAMESIZE_XY / 2) - (bounds.width / 2), 450);

	txt_gameOver.setFont(*newFont);
	txt_gameOver.setString("**** GameOver ****");
	txt_gameOver.setCharacterSize(24);
	txt_gameOver.setFillColor(sf::Color::Red);
	txt_gameOver.setStyle(sf::Text::Bold);
	bounds = txt_gameOver.getLocalBounds();
	txt_gameOver.setPosition((GAMESIZE_XY / 2) - (bounds.width / 2), 100);

	txt_playtimeFood.setFont(*newFont);
	txt_playtimeFood.setString("**** Dummy playtimefood ****");
	txt_playtimeFood.setCharacterSize(20);
	txt_playtimeFood.setFillColor(sf::Color::Green);
	txt_playtimeFood.setStyle(sf::Text::Bold);

	txt_totalScore.setFont(*newFont);
	txt_totalScore.setString("**** Dummy Total Score ****");
	txt_totalScore.setCharacterSize(20);
	txt_totalScore.setFillColor(sf::Color::Green);
	txt_totalScore.setStyle(sf::Text::Bold);
	
	txt_date.setFont(*newFont);
	txt_date.setString("**** Dummy Date ****");
	txt_date.setCharacterSize(20);
	txt_date.setFillColor(sf::Color::Green);
	txt_date.setStyle(sf::Text::Bold);

	txt_newHighScoreAchieved.setFont(*newFont);
	txt_newHighScoreAchieved.setString("!! Congrats, you achieved a new highscore !!");
	txt_newHighScoreAchieved.setCharacterSize(20);
	txt_newHighScoreAchieved.setFillColor(sf::Color::Green);
	txt_newHighScoreAchieved.setStyle(sf::Text::Bold);
	bounds = txt_newHighScoreAchieved.getLocalBounds();
	txt_newHighScoreAchieved.setPosition((GAMESIZE_XY / 2) - (bounds.width / 2), 375);

	txt_currentHighScoreScore.setFont(*newFont);
	txt_currentHighScoreScore.setString("**** Dummy currentHighScoreScore ****");
	txt_currentHighScoreScore.setCharacterSize(20);
	txt_currentHighScoreScore.setFillColor(sf::Color::Green);
	txt_currentHighScoreScore.setStyle(sf::Text::Bold);

	txt_currentHighScoreDate.setFont(*newFont);
	txt_currentHighScoreDate.setString("**** Dummy currentHighScoreDate ****");
	txt_currentHighScoreDate.setCharacterSize(20);
	txt_currentHighScoreDate.setFillColor(sf::Color::Green);
	txt_currentHighScoreDate.setStyle(sf::Text::Bold);
}


//--------------------------------------------------------------------------------------------------
//! @brief     	Destructor of Level class
//--------------------------------------------------------------------------------------------------
Level::~Level(){}


//--------------------------------------------------------------------------------------------------
//! @brief     	Creates boundaries that limit the map
//--------------------------------------------------------------------------------------------------
void Level::createBoundaries()
{
	for (int i = (stepSize / 2); i <= (GAMESIZE_XY - (stepSize / 2)); i += (stepSize / 2))
	{
		for (int j = (stepSize / 2); j <= (GAMESIZE_XY - (stepSize / 2)); j += (stepSize / 2))
		{
			if ((i == (stepSize / 2)) || (j == (stepSize / 2)) || (i == (GAMESIZE_XY - (stepSize / 2))) || (j == (GAMESIZE_XY - (stepSize / 2))))
			{
				boundary.setPosition(i - offsetOrigin, j - offsetOrigin);	// set the origin of each boundary
				boundaries.push_back(boundary);
			}
		}
	}
}


//--------------------------------------------------------------------------------------------------
//! @brief     	Checks for GameOver (when head of snake is in its body or boundaries)
//--------------------------------------------------------------------------------------------------
void Level::checkGameOver()
{
	// Starts at 1 because head is 0
	for (int i = 1; i < snake.snakePoints.size(); i++)
	{
		// Check if snakes head is in its body
		if ((snake.snakePoints[0].row) == (snake.snakePoints[i].row) &&
			(snake.snakePoints[0].col) == (snake.snakePoints[i].col))
		{
			gameOver = true;
		}
		// Check if snakes head is in boundaries
		else if ((snake.snakePoints[0].row == (stepSize/2)) || (snake.snakePoints[0].row == (GAMESIZE_XY - (stepSize/2)) ||
			(snake.snakePoints[0].col == (stepSize / 2)) || (snake.snakePoints[0].col == (GAMESIZE_XY - (stepSize/2)))))
		{
			gameOver = true;
		}
	}
}


//--------------------------------------------------------------------------------------------------
//! @brief     	Generates food at a random location on the field
//--------------------------------------------------------------------------------------------------
void Level::generateFood()
{
	bool foodGeneratedOnSnake = true;

	while (foodGeneratedOnSnake)
	{
		bool foodOnSnake = false;

		// example
		// Stepsize = 10;
		// firsPossibleValue would be 15 (-> 5 is not possible because its the center of a boundary)
		// lastPossibleValue would be 485 (-> 495 is not possible because its the center of a boundary)
		// moduloValue would be: (470)/10+1 => 48
		// with this we get values from 0 to 47
		// possible values could be:
		// ((0*stepsize) + firstpossiblevalue)
		// (0 * 10) + 15 = 15
		// (1 * 10) + 15 = 25
		// (2 * 10) + 15 = 35......
		// (47* 10) + 15 = 485

		int firsPossibleValue = ((stepSize/2) + stepSize);
		int lastPossibleValue = GAMESIZE_XY - ((stepSize / 2) + stepSize);

		int moduloValue = ((firsPossibleValue-lastPossibleValue) / stepSize) + 1;

		foodLocation.row = (((rand() % moduloValue)*stepSize) + firsPossibleValue);
		foodLocation.col = (((rand() % moduloValue)*stepSize) + firsPossibleValue);

		// check if food has been generated on snake
		for (int i = 0; i < snake.snakePoints.size(); i++)
		{
			if ((snake.snakePoints[i].row == foodLocation.row) && (snake.snakePoints[i].col == foodLocation.col))
			{
				foodOnSnake = true;
			}
		}

		if (foodOnSnake)
		{
			// Excute while loop one more time
			foodGeneratedOnSnake = true;
		}
		else
		{
			// Exit the while loop
			foodGeneratedOnSnake = false;
		}
	}

	// Set drawing origin for shape
	food.setPosition(foodLocation.col - offsetOrigin, foodLocation.row - offsetOrigin);
}


//--------------------------------------------------------------------------------------------------
//! @brief     	Adds new body part to snake if it has eaten some food
//--------------------------------------------------------------------------------------------------
void Level::eatFood()
{
	// Now there is no food on the field
	foodOnField = false;

	// New snake body part with a new location(0,0), will be overwritten when "updateSnake" method is executed
	Point newBodyPart;
	newBodyPart.row = 0;
	newBodyPart.col = 0;
	
	// Add the new body part at the end of the existing bodypart list
	snake.snakePoints.push_back(newBodyPart);

	// Food counter +1
	foodCount++;
}


//--------------------------------------------------------------------------------------------------
//! @brief     	Checks if the snake found the food on the field
//--------------------------------------------------------------------------------------------------
void Level::checkSnakeAteFood()
{
	if ((foodLocation.row == snake.snakePoints[0].row) && (foodLocation.col == snake.snakePoints[0].col))
	{
		eatFood();
	}
}


//--------------------------------------------------------------------------------------------------
//! @brief     	Calculates the stats of the game played
//--------------------------------------------------------------------------------------------------
void Level::calculateStats()
{
	// Get the time in seconds and round it
	timeElapsed = clock.getElapsedTime();
	timeElapsedSeconds = timeElapsed.asSeconds();
	timeElapsedSeconds = ceilf(timeElapsedSeconds * 100) / 100;
	
	// Calculate the score depending on the food eaten
	score = foodCount * 100;

	// Get the current date and time
	timeNow = time(0);
	localtime_s(&nowLocal, &timeNow);

	year = nowLocal.tm_year + 1900;
	month = nowLocal.tm_mon + 1;
	day = nowLocal.tm_mday;
	hour = nowLocal.tm_hour;
	minute = nowLocal.tm_min;
	seconds = nowLocal.tm_sec;
}


//--------------------------------------------------------------------------------------------------
//! @brief     	Shows the results in the console
//--------------------------------------------------------------------------------------------------
void Level::showStats()
{
	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!! GAME OVER !!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	cout << "Your Run lastet " << timeElapsedSeconds << " seconds! and ate " << foodCount << " Food! Good Job :)" << endl;
	cout << "Your total score is: " << score << " Keep up the good work!" << endl;
	cout << "Played on " << day << "." << month << "." << year << " at " << hour << ":" << minute << ":" << seconds << endl;
}


//--------------------------------------------------------------------------------------------------
//! @brief     	Prepares the stats for showing them in the main window
//--------------------------------------------------------------------------------------------------
void Level::prepareStats()
{
	stringstream stream;
	stream << setprecision(6) << timeElapsedSeconds;
	timeElapsedString = stream.str();
	
	scoreString = to_string(score);
	foodString = to_string(foodCount);

	yearString = to_string(year);
	
	// Some if statements for a better "look" 
	if (month > 9)
	{
		monthString = to_string(month);
	}
	else
	{
		monthString = "0" + to_string(month);
	}
	
	if (day > 9)
	{
		dayString = to_string(day);
	}
	else
	{
		dayString = "0" + to_string(day);
	}
	
	if (hour > 9)
	{
		hourString = to_string(hour);
	}
	else
	{
		hourString = "0" + to_string(hour);
	}

	if (minute > 9)
	{
		minuteString = to_string(minute);
	}
	else
	{
		minuteString = "0" + to_string(minute);
	}
	
	// Set texts for showing in the main window based on the stats achieved
	txt_playtimeFood.setString("You lasted " + timeElapsedString + " seconds" + " and ate " + foodString + " food");
	bounds = txt_playtimeFood.getLocalBounds();
	txt_playtimeFood.setPosition((GAMESIZE_XY / 2) - (bounds.width / 2), 200);

	txt_totalScore.setString("Your Score: " + scoreString + " Points");
	bounds = txt_totalScore.getLocalBounds();
	txt_totalScore.setPosition((GAMESIZE_XY / 2) - (bounds.width / 2), 250);

	txt_date.setString("Played on " + dayString + "." + monthString + "." + yearString + " at " + hourString + ":" + minuteString);
	bounds = txt_date.getLocalBounds();
	txt_date.setPosition((GAMESIZE_XY / 2) - (bounds.width / 2), 300);
}


//--------------------------------------------------------------------------------------------------
//! @brief     	Prepares the current highscore for showing it in the main window
//--------------------------------------------------------------------------------------------------
void Level::prepareCurrentHighscore()
{
	// Set some texts for the main window
	currentHighscoreScoreString = "Current Highscore: " + fileContent[0];	// Score from file
	currentHighscoreDateString = "Achieved at " + fileContent[1];			// Date from file

	txt_currentHighScoreScore.setString(currentHighscoreScoreString);
	bounds = txt_currentHighScoreScore.getLocalBounds();
	txt_currentHighScoreScore.setPosition((GAMESIZE_XY / 2) - (bounds.width / 2), 200);

	txt_currentHighScoreDate.setString(currentHighscoreDateString);
	bounds = txt_currentHighScoreDate.getLocalBounds();
	txt_currentHighScoreDate.setPosition((GAMESIZE_XY / 2) - (bounds.width / 2), 250);
}


//--------------------------------------------------------------------------------------------------
//! @brief     	Reads the current highscore stats from the file
//--------------------------------------------------------------------------------------------------
void Level::readHighScoresFromFile()
{
	std::ifstream inputFilestream;

	// Open the input filestream
	inputFilestream.open(pathToHighscoreFile);

	while (inputFilestream.good()) {

		// Read one line
		getline(inputFilestream, oneLine);

		// Push it at the end of the list
		fileContent.push_back(oneLine);
	}

	// Close the input file stream
	inputFilestream.close();
}


//--------------------------------------------------------------------------------------------------
//! @brief     	Writes the current highscore stats to the file
//--------------------------------------------------------------------------------------------------
void Level::writeHighScoresToFile()
{
	std::ofstream outputFilestream;

	// Open the output filestream
	outputFilestream.open(pathToHighscoreFile);

	// Write score and date to the file
	outputFilestream << to_string(currentHighscoreScore) << endl;
	outputFilestream << currentHighscoreDate;

	// Close the output file stream
	outputFilestream.close();
}