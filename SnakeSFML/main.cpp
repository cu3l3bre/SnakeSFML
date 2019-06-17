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

using namespace std;

int main()
{

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
	boundary.setPosition(-10, -10);
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
		//cout << "Loop" << endl;

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
		x += 30;
		y += 30;


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