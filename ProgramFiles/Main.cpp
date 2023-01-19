/*
  Author: Benjamin G. Friedman
  GitHub: benjamin-friedman
  Date: 01/19/23
  File: Main.cpp
  Description:
      - The main function for the solar system simulation program.
*/


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <memory>
#include <cmath>
#include <cctype>
#include "Planet.hpp"
#include "SolarSystem.hpp"




/***** Global Variables *****/
const int daysPerMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const int secondsPerDay = 86400;




/***** Functions declared/defined in this file *****/
// Validates the command line arguments
void validateCLA(int argc, char* argv[]);

// Initializes the variables that track total time and step time
void initializeTimeVariables(double& totalTime, double& stepTime, char* argv[]);

// Initializes the background image
void initializeBackgroundImage(sf::Image& backImg, sf::Texture& backText, sf::Sprite& backSprite,
	sf::Vector2u& backSize, const std::string& backImgFileName);

// Initializes the font used for all text
void initializeFont(sf::Font& font, const std::string& fontFileName);

// Initializes the strings to display the time elapsed in various forms - seconds, days, months, and years
void initializeTimeText(sf::Text& timeElapsedString, sf::Text& secondsPassed, sf::Text& daysPassed, sf::Text& monthsPassed,
	sf::Text& yearsPassed, const sf::Font& font);

// Initializes the poem verses
void initializePoemText(sf::Text& doNot, const std::string& doNotVerse, sf::Text& rage, const std::string& rageVerse,
	const sf::Font& font, const sf::Vector2u& backSize);

// Initializes the song
void initializeSong(sf::Music& song, const std::string& songFileName);


// Updates the time information during the simulation
void updateTimeInformation(double timeElapsed, int& totalSecondsPassed, int& totalDaysPassed, int& daysThisMonth,
	const int daysPerMonth[], size_t& daysPerMonthIndex, int& totalMonthsPassed, int& monthsThisYear, int& totalYearsPassed,
	sf::Text& secondsPassed, sf::Text& daysPassed, sf::Text& monthsPassed, sf::Text& yearsPassed);




int main(int argc, char* argv[]) {

	/* simulation initializations */
	// validate command line arguments
	validateCLA(argc, argv);
	

	// variables to track the time
	double totalTime;
	double stepTime;
	double timeElapsed{ 0 };
	initializeTimeVariables(totalTime, stepTime, argv);


	// background image
	sf::Image backImg;
	sf::Texture backText;
	sf::Sprite backSprite;
	sf::Vector2u backSize;
	initializeBackgroundImage(backImg, backText, backSprite, backSize, "res/SPACE_BACKGROUND_CROPPED.gif");


	// font used in all text
	sf::Font font;
	initializeFont(font, "res/arial.ttf");


	// all the texts and numbers to display the time information
	sf::Text timeElapsedString;
	sf::Text secondsPassed;
	int totalSecondsPassed{ 0 };
	sf::Text daysPassed;
	int totalDaysPassed{ 0 };
	sf::Text monthsPassed;
	int totalMonthsPassed{ 0 };
	sf::Text yearsPassed;
	int totalYearsPassed{ 0 };
	int daysThisMonth{ 0 };
	size_t daysPerMonthIndex{ 0 };
	int monthsThisYear{ 0 };
	initializeTimeText(timeElapsedString, secondsPassed, daysPassed, monthsPassed, yearsPassed, font);


	// poem verse
	sf::Text doNot;
	sf::Text rage;
	initializePoemText(doNot, "Do not go gentle into that good night", rage, "Rage, rage against the dying of the light", font, backSize);


	// song
	sf::Music song;
	initializeSong(song, "res/Main_Theme_Interstellar.ogg");




	/* initialize the solar system from res/solar_system.txt */
	SolarSystem solarSystem(backSize);
	std::cin >> solarSystem;




	/* start the simulation */
	sf::RenderWindow window(sf::VideoMode(backSize.x, backSize.y), "Background");
	song.play();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// play song again if it stopped
		if (song.getStatus() == sf::Music::Stopped) {
			song.stop();
			song.play();
		}


		// update all of the time information
		updateTimeInformation(timeElapsed, totalSecondsPassed, totalDaysPassed, daysThisMonth, daysPerMonth, daysPerMonthIndex,
			totalMonthsPassed, monthsThisYear,totalYearsPassed, secondsPassed, daysPassed, monthsPassed, yearsPassed);

		// simulate one step of the solar system
		solarSystem.step(stepTime);

		// clear window, redraw everything
		window.clear();
		window.draw(backSprite);
		window.draw(timeElapsedString);
		window.draw(secondsPassed);
		window.draw(daysPassed);
		window.draw(monthsPassed);
		window.draw(yearsPassed);
		window.draw(doNot);
		window.draw(rage);
		window.draw(solarSystem);
		window.display();

		// advance the time elapsed, check if simulation has finished
		timeElapsed += stepTime;
		if (timeElapsed >= totalTime)
			break;
	}


	/* output final state of solar system */
	std::cout << "\nFINAL STATE OF SOLAR SYSTEM\n";
	std::cout << solarSystem;

	
	return 0;
}




/***** Functions declared/defined in this file *****/
void validateCLA(int argc, char* argv[]) {
	// invalid # of CLA
	if (argc != 3) {
		std::cout << "Error: ./SolarSystemSimulation [total time] [time of step] < res/solar_system.txt\n";
		exit(1);
	}

	// argv[1] and argv[2] are not positive integers
	std::string argv1(argv[1]);
	std::string argv2(argv[2]);
	for (auto& ch : argv1) {
		if (!isdigit(ch)) {
			std::cout << "Error: ./SolarSystemSimulation [total time] [time of step] < res/solar_system.txt\n";
			exit(1);
		}
	}
	for (auto& ch : argv2) {
		if (!isdigit(ch)) {
			std::cout << "Error: ./SolarSystemSimulation [total time] [time of step] < res/solar_system.txt\n";
			exit(1);
		}
	}
}


void initializeTimeVariables(double& totalTime, double& stepTime, char* argv[]) {
	std::string totalTime2(argv[1]);
	std::string stepTime2(argv[2]);
	std::string::size_type sz;

	totalTime = stod(totalTime2, &sz);
	stepTime = stod(stepTime2, &sz);
}


void initializeBackgroundImage(sf::Image& backImg, sf::Texture& backText, sf::Sprite& backSprite, sf::Vector2u& backSize, const std::string& backImgFileName) {
	if (!backImg.loadFromFile(backImgFileName)) {
		std::cout << "Failed to load background image with file name: " << backImgFileName << std::endl;
		exit(2);
	}

	backText.loadFromImage(backImg);
	backSprite.setTexture(backText);
	backSize = backImg.getSize();
}


void initializeFont(sf::Font& font, const std::string& fontFileName) {
	if (!font.loadFromFile(fontFileName)) {
		std::cout << "Error. Failed to load font file with file name: " << fontFileName << std::endl;
		exit(3);
	}
}


void initializeTimeText(sf::Text& timeElapsedString, sf::Text& secondsPassed, sf::Text& daysPassed, sf::Text& monthsPassed,
	sf::Text& yearsPassed, const sf::Font& font)
{
	timeElapsedString.setFont(font);
	timeElapsedString.setFillColor(sf::Color::White);
	timeElapsedString.setCharacterSize(15);
	timeElapsedString.setString("Time Elapsed");

	secondsPassed.setFont(font);
	secondsPassed.setFillColor(sf::Color::White);
	secondsPassed.setCharacterSize(15);
	secondsPassed.setPosition(0, 15);

	daysPassed.setFont(font);
	daysPassed.setFillColor(sf::Color::White);
	daysPassed.setCharacterSize(15);
	daysPassed.setPosition(0, 30);

	monthsPassed.setFont(font);
	monthsPassed.setFillColor(sf::Color::White);
	monthsPassed.setCharacterSize(15);
	monthsPassed.setPosition(0, 45);

	yearsPassed.setFont(font);
	yearsPassed.setFillColor(sf::Color::White);
	yearsPassed.setCharacterSize(15);
	yearsPassed.setPosition(0, 60);
}


void initializePoemText(sf::Text& doNot, const std::string& doNotVerse, sf::Text& rage, const std::string& rageVerse,
	const sf::Font& font, const sf::Vector2u& backSize) {
	doNot.setFont(font);
	doNot.setFillColor(sf::Color::White);
	doNot.setCharacterSize(30);
	doNot.setString(doNotVerse);
	doNot.setPosition(static_cast<float>(backSize.x / 4), static_cast<float>(backSize.y / 4));

	rage.setFont(font);
	rage.setFillColor(sf::Color::White);
	rage.setString(rageVerse);
	rage.setCharacterSize(30);
	rage.setPosition(static_cast<float>(backSize.x / 4), static_cast<float>(3 * backSize.y / 4));
}


void initializeSong(sf::Music& song, const std::string& songFileName) {
	if (!song.openFromFile(songFileName)) {
		std::cout << "Failed to open music file with file name: " << songFileName << std::endl;
		exit(4);
	}
}


void updateTimeInformation(double timeElapsed, int& totalSecondsPassed, int& totalDaysPassed, int& daysThisMonth,
	const int daysPerMonth[], size_t& daysPerMonthIndex, int& totalMonthsPassed, int& monthsThisYear, int& totalYearsPassed,
	sf::Text& secondsPassed, sf::Text& daysPassed, sf::Text& monthsPassed, sf::Text& yearsPassed)
{
	// seconds passed
	totalSecondsPassed = static_cast<int>(timeElapsed);

	// days passed
	int previousTotalDaysPassed = totalDaysPassed;
	totalDaysPassed = totalSecondsPassed / secondsPerDay;

	// months and years passed
	if (previousTotalDaysPassed < totalDaysPassed)
		++daysThisMonth;
	if (daysThisMonth == daysPerMonth[daysPerMonthIndex]) {
		daysThisMonth = 0;
		daysPerMonthIndex = daysPerMonthIndex < 11 ? daysPerMonthIndex + 1 : 0;
		++totalMonthsPassed;
		++monthsThisYear;
		if (monthsThisYear == 12) {
			monthsThisYear = 0;
			++totalYearsPassed;
		}
	}
	
	secondsPassed.setString("Seconds passed: " + std::to_string(totalSecondsPassed));
	daysPassed.setString("Days passed: " + std::to_string(totalDaysPassed));
	monthsPassed.setString("Months passed: " + std::to_string(totalMonthsPassed));
	yearsPassed.setString("Years passed: " + std::to_string(totalYearsPassed));
}