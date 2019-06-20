//**************************************************************************************************
/*!
 @file           level.h
 @brief          Declaration of Level class
 @date           17.06.2019
 @author         Daniel Schmunkamp
 */
 //**************************************************************************************************

#pragma once

#include "point.h"
#include <vector>
#include <fstream>
#include <string>
#include "time.h"
#include "snake.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Clock.hpp>


// Class Level
class Level
{
public:

	Snake snake;

	Point foodLocation;
	bool foodOnField;
	int foodCount;

	bool gameRunning;
	bool gameOver;
	int score;
	
	std::string pathToHighscoreFile;
	std::string oneLine;
	std::vector<std::string> fileContent;

	int currentHighscoreScore;
	std::string currentHighscoreDate;

	std::string scoreString;
	std::string foodString;
	std::string timeElapsedString;
	std::string yearString;
	std::string monthString;
	std::string dayString;
	std::string hourString;
	std::string minuteString;

	std::string currentHighscoreScoreString;
	std::string currentHighscoreDateString;
	

	sf::Time timeElapsed;
	float timeElapsedSeconds;
	sf::Clock clock;

	tm nowLocal;
	time_t timeNow;
	time_t gameStartTime;
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int seconds;


	int circleRadius;
	int stepSize;
	int offsetOrigin;

	sf::Vector2f rectangleSize;
	sf::RectangleShape boundary;
	std::vector<sf::RectangleShape> boundaries;

	sf::CircleShape food;

	sf::FloatRect bounds;
	sf::Text txt_instrcution;
	sf::Text txt_instrcution2;
	sf::Text txt_instrcution3;
	sf::Text txt_gameOver;
	sf::Text txt_playtimeFood;
	sf::Text txt_totalScore;
	sf::Text txt_date;
	sf::Text txt_currentHighScoreScore;
	sf::Text txt_currentHighScoreDate;
	sf::Text txt_newHighScoreAchieved;


	Level();			// Constructor
	Level(sf::Font*);	// Constructor with has the fonts as paramter
	~Level();			// Destructor

	// Methods

	void createBoundaries();		// Creates the boundaries that limit the field
	void checkGameOver();			// Checks if the GameOver condition is satisfied
	void generateFood();			// Places food on the field
	void eatFood();					// Lets the snake eat food and grow
	void checkSnakeAteFood();		// Checks if the snake ate the food
	void calculateStats();			// Calculates some stats after the game is over
	void showStats();				// Prints out the stats in the console 
	void prepareStats();			// Prepares the stats to show them in the main window
	void prepareCurrentHighscore();	// Prepares the current highscore to show it in the main window
	void readHighScoresFromFile();	// Reads the current highscore stats from the file
	void writeHighScoresToFile();	// Writes the current highscore stats to the file
};