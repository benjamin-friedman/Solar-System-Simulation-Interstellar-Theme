/*
  Author: Benjamin G. Friedman
  GitHub: benjamin-friedman
  Date: 01/19/23
  File: SolarSystem.cpp
  Description:
      - Implementation file for the SolarSystem class.
*/


#include "SolarSystem.hpp"


// radius = -1 is some default placeholder value
SolarSystem::SolarSystem(sf::Vector2u backSize) : win(backSize), radius(-1) {}


void SolarSystem::addPlanet(std::unique_ptr<Planet>& planet) {
	planets.push_back(std::move(planet));
}


void SolarSystem::step(double stepTime) {
	// update the force components of each planet
	for (size_t i = 0; i < planets.size(); ++i) {
		double x_force{ 0 };
		double y_force{ 0 };
		for (size_t j = 0; j < planets.size(); ++j) {
			if (i != j) {
				x_force += planets[i]->forceX(*planets[j]);
				y_force += planets[i]->forceY(*planets[j]);
			}
		}
		planets[i]->setForce(x_force, y_force);
	}

	// Now the force components have been updated in every planet.
	// Adjust the velocities, x/y coordinates, and image position.
	for (size_t i = 0; i < planets.size(); ++i)
		planets[i]->step(stepTime);
}


std::istream& operator>>(std::istream& input, SolarSystem& solarSystem) {
	// get the total number of planets and radius of the solar system
	int numPlanets;
	std::cin >> numPlanets;
	std::cin >> solarSystem.radius;

	// information for an individual planet
	double x_pos, y_pos, x_vel, y_vel, mass;
	std::string fileName;

	for (int i = 0; i < numPlanets; ++i) {
		input >> x_pos >> y_pos >> x_vel >> y_vel >> mass >> fileName;
		fileName = "res/" + fileName;
		std::unique_ptr<Planet> planet(std::make_unique<Planet>(x_pos, y_pos, x_vel, y_vel, mass,
			solarSystem.radius, solarSystem.win, fileName));
		solarSystem.addPlanet(planet);
	}

	return input;	
}


std::ostream& operator<<(std::ostream& output, const SolarSystem& solarSystem) {
	std::cout << "Planets: " << solarSystem.planets.size() << std::endl;
	std::cout << "Solar System Radius: " << solarSystem.radius << std::endl;

	// save output flags
	std::ios_base::fmtflags flagSettings = std::cout.flags();
	// left justified and sci not
	std::cout.setf(std::ios::left | std::ios::scientific);
	std::cout.precision(4);
	std::cout << std::setw(15) << "...xpos..." << std::setw(15) << "...ypos...";
	std::cout << std::setw(15) << "...xvel..." << std::setw(15) << "...yvel...";
	std::cout << std::setw(15) << "...mass..." << std::setw(15) << "filename" << std::endl;
	std::cout.flags(flagSettings);


	for (size_t i = 0; i < solarSystem.planets.size(); ++i)
		std::cout << *solarSystem.planets[i] << std::endl;
	std::cout << std::endl;

	return output;
}

void SolarSystem::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	for (size_t i = 0; i < planets.size(); ++i)
		target.draw(*planets[i], states);
}