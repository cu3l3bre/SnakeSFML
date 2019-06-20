//////////////////////////////////////////////////////////////////////////////////////////////
//																							//
//	Author:		DS																			//
//	Created:	2019.06.17																	//
//																							//
//////////////////////////////////////////////////////////////////////////////////////////////


#include "level.h"
#include <iostream>

using namespace std;


Level::Level()
{
}

// STD - Constructor
Level::Level(sf::Font* newFont)
{
	circleRadius = STEPSIZE / 2;
	stepSize = STEPSIZE;
	offsetOrigin = STEPSIZE / 2;


	pathToHighscoreFile = "Highscores.txt";
	//inputFilestream(pathToHighscoreFile);
	//outputFilestream;

	//currentHighscoreScore = 0;
	//currentHighscoreDate = "";

	gameRunning = false;
	gameOver = false;
	foodOnField = false;
	foodCount = 0;
	score = 0.0;

	rectangleSize.x = stepSize;
	rectangleSize.y = stepSize;

	boundary.setSize(rectangleSize);
	boundary.setFillColor(sf::Color::Red);

	food.setRadius(circleRadius);
	food.setFillColor(sf::Color::Yellow);


	txt_instrcution.setFont(*newFont);
	txt_instrcution.setString("Press [s] to start or [q] to quit");
	txt_instrcution.setCharacterSize(24);
	txt_instrcution.setFillColor(sf::Color::Green);
	txt_instrcution.setStyle(sf::Text::Bold);
	bounds = txt_instrcution.getLocalBounds();
	txt_instrcution.setPosition((500 / 2) - (bounds.width / 2), 100);

	
	txt_instrcution2.setFont(*newFont);
	txt_instrcution2.setString("Use [a] for left or [d] for right to control the snake GLHF");
	txt_instrcution2.setCharacterSize(16);
	txt_instrcution2.setFillColor(sf::Color::Green);
	txt_instrcution2.setStyle(sf::Text::Bold);
	bounds = txt_instrcution2.getLocalBounds();
	txt_instrcution2.setPosition((500 / 2) - (bounds.width / 2), 450);


	
	txt_instrcution3.setFont(*newFont);
	txt_instrcution3.setString("Use [b] to go back to the menu or [q] to quit");
	txt_instrcution3.setCharacterSize(16);
	txt_instrcution3.setFillColor(sf::Color::Green);
	txt_instrcution3.setStyle(sf::Text::Bold);
	bounds = txt_instrcution3.getLocalBounds();
	txt_instrcution3.setPosition((500 / 2) - (bounds.width / 2), 450);


	txt_gameOver.setFont(*newFont);
	txt_gameOver.setString("**** GameOver ****");
	txt_gameOver.setCharacterSize(24);
	txt_gameOver.setFillColor(sf::Color::Red);
	txt_gameOver.setStyle(sf::Text::Bold);
	bounds = txt_gameOver.getLocalBounds();
	txt_gameOver.setPosition((500 / 2) - (bounds.width / 2), 100);


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
	txt_newHighScoreAchieved.setPosition((500 / 2) - (bounds.width / 2), 350);






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


// Destructor
Level::~Level(){}


// Methods


// GameOver is When Head of Snake is in its body or boundaries
void Level::checkGameOver()
{
	//bool gameOver = false;
	// Starts at 1 because Head is 0
	for (int i = 1; i < snake.snakePoints.size(); i++)
	{
		// Check if snakes head is in its body
		if ((snake.snakePoints[0].row) == (snake.snakePoints[i].row) &&
			(snake.snakePoints[0].col) == (snake.snakePoints[i].col))
		{
			gameOver = true;
		}
		// Check if snakes head is in boundaries
		else if ((snake.snakePoints[0].row == (stepSize/2)) || (snake.snakePoints[0].row == (500 - (stepSize/2)) ||
			(snake.snakePoints[0].col == (stepSize / 2)) || (snake.snakePoints[0].col == (500 - (stepSize/2)))))
		{
			gameOver = true;
		}
	}
}


// Generate food at random location
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
		int lastPossibleValue = 500 - ((stepSize / 2) + stepSize);

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


//add new body part to snake if it has eaten some food
void Level::eatFood()
{
	foodOnField = false;
	Point newBodyPart;
	newBodyPart.row = 0;
	newBodyPart.col = 0;
	snake.snakePoints.push_back(newBodyPart);
	foodCount++;
}


// Calculate the stats of the game played
void Level::calculateStats()
{
	timeElapsed = clock.getElapsedTime();

	score = round((((foodCount + 1) * 10) - (timeElapsed.asSeconds()*0.4)) * 100);

	timeNow = time(0);
	localtime_s(&nowLocal, &timeNow);

	year = nowLocal.tm_year + 1900;
	month = nowLocal.tm_mon + 1;
	day = nowLocal.tm_mday;
	hour = nowLocal.tm_hour;
	minute = nowLocal.tm_min;
	seconds = nowLocal.tm_sec;
}

// Show the results in the console
void Level::showStats()
{
	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!! GAME OVER !!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	cout << "Your Run lastet " << timeElapsed.asSeconds() << " seconds! and ate " << foodCount << " Food! Good Job :)" << endl;
	cout << "Your total score is: " << score << " Keep up the good work!" << endl;
	cout << "Played on " << day << "." << month << "." << year << " at " << hour << ":" << minute << ":" << seconds << endl;
}


// Create Boundaries that limit the map
void Level::createBoundaries()
{
	for (int i = (stepSize/2); i <= (500-(stepSize/2)); i += (stepSize/2))
	{
		for (int j = (stepSize / 2); j <= (500 - (stepSize / 2)); j += (stepSize / 2))
		{
			if ((i == (stepSize / 2)) || (j == (stepSize / 2)) || (i == (500 - (stepSize / 2))) || (j == (500 - (stepSize / 2))))
			{

				boundary.setPosition(i - offsetOrigin, j - offsetOrigin);	// set the origin of each boundary
				boundaries.push_back(boundary);
			}
		}
	}


}

// Check if the snake ate something and let it grow if so
void Level::checkSnakeAteFood()
{
	if ((foodLocation.row == snake.snakePoints[0].row) && (foodLocation.col == snake.snakePoints[0].col))
	{
		eatFood();
	}

}


// prepare stats for showing in main window
void Level::prepareStats()
{
	scoreString = to_string(score);
	foodString = to_string(foodCount);
	timeElapsedString = to_string(timeElapsed.asSeconds());
	yearString = to_string(year);
	monthString = to_string(month);
	dayString = to_string(day);
	hourString = to_string(hour);
	minuteString = to_string(minute);

	txt_playtimeFood.setString("You lasted " + timeElapsedString + " seconds" + " and ate " + foodString + " food");

	bounds = txt_playtimeFood.getLocalBounds();
	txt_playtimeFood.setPosition((500 / 2) - (bounds.width / 2), 150);


	txt_totalScore.setString("Your Score: " + scoreString + " Points");

	bounds = txt_totalScore.getLocalBounds();
	txt_totalScore.setPosition((500 / 2) - (bounds.width / 2), 200);


	txt_date.setString("Played on " + dayString + "." + monthString + "." + yearString + " at " + hourString + ":" + minuteString);
	bounds = txt_date.getLocalBounds();
	txt_date.setPosition((500 / 2) - (bounds.width / 2), 250);

}


void Level::readHighScoresFromFile()
{
	std::ifstream inputFilestream;

	inputFilestream.open(pathToHighscoreFile);

	while (inputFilestream.good()) {

		// lesen einer Zeile
		getline(inputFilestream, oneLine);

		// diese Zeile ans Ende der Liste anfügen
		fileContent.push_back(oneLine);
	}

	inputFilestream.close();
	inputFilestream.clear();
	
}



void Level::writeHighScoresToFile()
{

	std::ofstream outputFilestream;

	outputFilestream.open(pathToHighscoreFile);
	outputFilestream << to_string(currentHighscoreScore) << endl;
	outputFilestream << currentHighscoreDate;
	outputFilestream.close();
}


// raus
void Level::checkNewHighscore()
{
	if (score > currentHighscoreScore)
	{
		currentHighscoreScore = score;
		currentHighscoreDate = dayString + "." + monthString + "." + yearString + " at " + hourString + ":" + minuteString;
	}

}

void Level::prepareCurrentHighscore()
{

	currentHighscoreScoreString = "Current Highscore: " + fileContent[0];
	currentHighscoreDateString = "Achieved at " + fileContent[1];


	txt_currentHighScoreScore.setString(currentHighscoreScoreString);
	bounds = txt_currentHighScoreScore.getLocalBounds();
	txt_currentHighScoreScore.setPosition((500 / 2) - (bounds.width / 2), 250);

	txt_currentHighScoreDate.setString(currentHighscoreDateString);
	bounds = txt_currentHighScoreDate.getLocalBounds();
	txt_currentHighScoreDate.setPosition((500 / 2) - (bounds.width / 2), 300);
}