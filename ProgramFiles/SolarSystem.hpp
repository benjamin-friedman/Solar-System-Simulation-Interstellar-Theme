/*
  Author: Benjamin G. Friedman
  GitHub: benjamin-friedman
  Date: 01/19/23
  File: SolarSystem.hpp
  Description:
      - Header file for the SolarSystem class.
*/


#pragma once


#include "Planet.hpp"
#include <vector>
#include <memory>


class SolarSystem  : public sf::Drawable
{
public:
	// constructor
	SolarSystem(sf::Vector2u backSize);

	// add a planet to the solar system
	void addPlanet(std::unique_ptr<Planet>& planet);

	// adjust the positions of all planets in one time step
	void step(double stepTime);

	// input all of the solar system information - # of planets, radius, and planet information
	friend std::istream& operator>>(std::istream& input, SolarSystem& solarSystem);

	// output all of the solar system information - # of planets, radius, and planet information
	friend std::ostream& operator<<(std::ostream& output, const SolarSystem& solarSystem);


private:
	// SFML draw
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	std::vector<std::unique_ptr<Planet>> planets;    // planets
	sf::Vector2u win;                                // window dimensions
	double radius;                                   // radius of solar system
};