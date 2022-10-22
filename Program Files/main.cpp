#include "CelestialBody.h"
#include "Universe.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <memory>
#include <cmath>

const int daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const int secondsPerDay = 86400;


void printHeader();

int main(int argc, char* argv[]) {
	// check command line arguments
	if (argc != 3) {
		std::cout << "Error: ./NBody [total time] [time of step] < planets.txt\n";
		exit(1);
	}

	// initialize variables to track the time
	std::string totalTime2(argv[1]);
	std::string stepTime2(argv[2]);
	std::string::size_type sz;

	double totalTime = stod(totalTime2, &sz);
	double stepTime = stod(stepTime2, &sz);
	double timeElapsed{ 0 };


	// load background images
	sf::Image backImg;
	if (!backImg.loadFromFile("SPACE_BACKGROUND_CROPPED.gif")) {
		std::cout << "Failed to load background image\n";
		exit(1);
	}

	sf::Texture backText;
	backText.loadFromImage(backImg);
	sf::Sprite backSprite;
	backSprite.setTexture(backText);
	sf::Vector2u backSize = backImg.getSize();

	int numBodies;
	double universeRadius;
	std::cin >> numBodies;
	std::cin >> universeRadius;

	// set up the universe
	Universe universe;
	for (int i = 0; i < numBodies; i++) {

		std::unique_ptr<CelestialBody> cBody(std::make_unique<CelestialBody>());
		std::cin >> *cBody;
		cBody->setRadius(universeRadius);
		cBody->setWindow(backSize.x, backSize.y);
		cBody->setPosition();
		universe.addBody(cBody);
	}

	// font used in all text
	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		std::cout << "Error. Failed to load font file\n\n";
		exit(1);
	}

	// all the texts to display the time information
	sf::Text timeElapsedString;
	timeElapsedString.setFont(font);
	timeElapsedString.setFillColor(sf::Color::White);
	timeElapsedString.setCharacterSize(15);
	timeElapsedString.setString("Time Elapsed");

	sf::Text secondsPassed;
	secondsPassed.setFont(font);
	secondsPassed.setFillColor(sf::Color::White);
	secondsPassed.setCharacterSize(15);
	secondsPassed.setPosition(0, 15);

	sf::Text daysPassed;
	daysPassed.setFont(font);
	daysPassed.setFillColor(sf::Color::White);
	daysPassed.setCharacterSize(15);
	daysPassed.setPosition(0, 30);

	sf::Text monthsPassed;
	monthsPassed.setFont(font);
	monthsPassed.setFillColor(sf::Color::White);
	monthsPassed.setCharacterSize(15);
	monthsPassed.setPosition(0, 45);

	sf::Text yearsPassed;
	yearsPassed.setFont(font);
	yearsPassed.setFillColor(sf::Color::White);
	yearsPassed.setCharacterSize(15);
	yearsPassed.setPosition(0, 60);

	// poem verse
	sf::Text doNot;
	doNot.setFont(font);
	doNot.setFillColor(sf::Color::White);
	doNot.setCharacterSize(30);
	doNot.setString("Do not go gentle into that good night");
	doNot.setPosition(static_cast<float>(backSize.x / 4), static_cast<float>(backSize.y / 4));

	sf::Text rage;
	rage.setFont(font);
	rage.setFillColor(sf::Color::White);
	rage.setString("Rage, rage against the dying of the light");
	rage.setCharacterSize(30);
	rage.setPosition(static_cast<float>(backSize.x / 4), static_cast<float>(3 * backSize.y / 4));


	// music
	sf::Music song;
	if (!song.openFromFile("Main_Theme_Interstellar.ogg")) {
		std::cout << "Failed to open music file\n";
		exit(1);
	}
	song.play();


	/* Start the simulation */
	sf::RenderWindow window(sf::VideoMode(backSize.x, backSize.y), "Background");

	int totalSecondsPassed{ 0 };
	int totalDaysPassed{ 0 };
	int totalMonthsPassed{ 0 };
	int totalYearsPassed{ 0 };

	int daysThisMonth{ 0 };
	int daysPerMonthIndex{ 0 };
	int monthsThisYear{ 0 };
	
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

		// clear window, redraw everything
		window.clear();
		window.draw(backSprite);			// background image
		window.draw(timeElapsedString);		// "Time Elapsed" message

		// seconds passed
		totalSecondsPassed = static_cast<int>(timeElapsed);

		// days passed
		int previousTotalDaysPassed = totalDaysPassed;
		totalDaysPassed = totalSecondsPassed / secondsPerDay;

		// months and years passed
		if (previousTotalDaysPassed < totalDaysPassed)
			daysThisMonth++;
		if (daysThisMonth == daysPerMonth[daysPerMonthIndex]) {
			daysThisMonth = 0;
			daysPerMonthIndex = daysPerMonthIndex < 11 ? daysPerMonthIndex + 1 : 0;
			totalMonthsPassed++;
			monthsThisYear++;
			if (monthsThisYear == 12) {
				monthsThisYear = 0;
				totalYearsPassed++;
			}
		}
		
		secondsPassed.setString("Seconds passed: " + std::to_string(totalSecondsPassed));
		daysPassed.setString("Days passed: " + std::to_string(totalDaysPassed));
		monthsPassed.setString("Months passed: " + std::to_string(totalMonthsPassed));
		yearsPassed.setString("Years passed: " + std::to_string(totalYearsPassed));
		window.draw(secondsPassed);
		window.draw(daysPassed);
		window.draw(monthsPassed);
		window.draw(yearsPassed);
		window.draw(doNot);
		window.draw(rage);

		


		/* Go through every body 1 by 1 and update the force components */
		for (int i = 0; i < universe.getNumBodies(); i++) {
			double x_force{ 0 };
			double y_force{ 0 };
			for (int j = 0; j < universe.getNumBodies(); j++) {
				if (i != j) {
					x_force += (universe.getBody(i))->forceX(*universe.getBody(j));
					y_force += (universe.getBody(i))->forceY(*universe.getBody(j));
				}
			}
			(universe.getBody(i))->setForce(x_force, y_force);
		}

		/* Now the force components have been updated in every body. Adjust the
		   velocities, x-y- coordinates, and image position */
		for (int i = 0; i < universe.getNumBodies(); i++) {
			(universe.getBody(i))->step(stepTime);
			(universe.getBody(i))->setPosition();
		}

		/* Display all celestial bodies */
		for (int i = 0; i < universe.getNumBodies(); i++) {
			window.draw(*universe.getBody(i));
		}

		window.display();

		timeElapsed += stepTime;

		if (timeElapsed >= totalTime)
			break;
	}


	/* Output final state of universe */
	std::cout << "\nFINAL STATE OF UNIVERSE\n";
	std::cout << "Celestial Bodies: " << numBodies << std::endl;
	std::cout << "Universe Radius: " << universeRadius << std::endl;
	printHeader();

	for (int i = 0; i < universe.getNumBodies(); i++)
		std::cout << *universe.getBody(i) << std::endl;
	std::cout << std::endl;
	return 0;
}


void printHeader(void) {
	// save output flags
	std::ios_base::fmtflags flagSettings = std::cout.flags();
	// left justified and sci not
	std::cout.setf(std::ios::left | std::ios::scientific);
	std::cout.precision(4);
	std::cout << std::setw(12) << "...xpos..." << std::setw(12) << "...ypos...";
	std::cout << std::setw(12) << "...xvel..." << std::setw(12) << "...yvel...";
	std::cout << std::setw(12) << "...mass..." << std::setw(12) << "filename" << std::endl;
	std::cout.flags(flagSettings);
}
