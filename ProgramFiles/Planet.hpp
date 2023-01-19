/*
  Author: Benjamin G. Friedman
  GitHub: benjamin-friedman
  Date: 01/19/23
  File: Planet.hpp
  Description:
      - Header file for the Planet class.
*/


#pragma once


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>
#include <cmath>
#include <iomanip>


class Planet : public sf::Drawable
{
public:
	// constructor
	Planet(double _x_pos, double _y_pos, double _x_vel, double _y_vel, double _mass,
		double _solarSystemRadius, sf::Vector2u _win, const std::string& _fileName);

	/* Coordinates x_pos and y_pos are for a regular x-y plane with the origin
	   at the center of the screen. SFML origin (0, 0) is actually the top left
	   corner so this function adjusts the actual coordinates of the sprite to
	   account for this. This function is called during initialization (constructor)
	   and when updating the planet's position during one time step (step). */
	void setPosition();
	
	// sets the x-y force components
	void setForce(double _x_force, double _y_force);
	
	// returns the x and y forces between calling object and planet */
	double forceX(const Planet& planet) const;
	double forceY(const Planet& planet) const;

	/* Initiates a single time step. Updates the x-y coordinates, velocity, and image
	   position. setForce must have been called before this to update the force components
	   since all these calculations are based on the force components. timeStep was
	   passed as on of the command line arguments*/
	void step(double timeStep);
	
	// output all of the planet information for each planet originally in res/solar_system.txt
	// x-y coordinates, x-y velocities, mass, and image file name
	friend std::ostream& operator<<(std::ostream& output, const Planet& planet);

	// gravitational constant
	static constexpr double G = 6.67e-11;


private:
	// SFML draw
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	// info about planet
	double x_pos, y_pos;	       // x and y position
	double x_vel, y_vel;	       // x and y velocity
	double x_force, y_force;	   // x and y force components
	double x_accel, y_accel;	   // x and y acceleration
	double mass;	               // mass of planet
	double solarSystemRadius;      // radius of the solar system it exists in
	sf::Vector2u win;              // window dimensions
	std::string fileName;          // file containing planet image


	// image objects
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
};
