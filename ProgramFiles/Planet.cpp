/*
  Author: Benjamin G. Friedman
  GitHub: benjamin-friedman
  Date: 01/19/23
  File: Planet.cpp
  Description:
      - Implementation file for the Planet class.
*/


#include "Planet.hpp"


Planet::Planet(double _x_pos, double _y_pos, double _x_vel, double _y_vel, double _mass,
		double _solarSystemRadius, sf::Vector2u _win, const std::string& _fileName) :
	x_pos(_x_pos), y_pos(_y_pos), x_vel(_x_vel), y_vel(_y_vel), mass(_mass),
	solarSystemRadius(_solarSystemRadius), win(_win), fileName(_fileName)
{
	if (!image.loadFromFile(fileName)) {
		std::cout << "Here\n";
		std::cout << "Failed to load image file named " << fileName << std::endl;
		exit(1);
	}

	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setPosition(x_pos, y_pos);

	setPosition();
}


void Planet::setPosition() {
	sf::Vector2u origin(win.x / 2.0, win.y / 2.0);	// get coordinates of center of window

	/* Optional - Instead of using the actual window dimensions, use an adjusted dimension that is 10% smaller
	   (this gives a 5% margin going around the border. This prevents a planet from being dispalyed
	   partially outside the window. In the math below, if this adjustment were not there, then
	   a planet whose x or y coordinates were the same as the solar system's radius would be displayed
	   partially out the window. */
	// double adjustedWinWidth = winWidth * 0.9;
	// double adjustedWinHeight = winHeight * 0.9;

	/* Steps to set the position
	     - Get the ratio of each coordinate to the radius
	     - Multiply that by half the width/height to get the right proportion of it's x-length or y-length
	     - The (0, 0) position in SFML is actually the top left corner and not the center of the screen like
		   in an x-y plane. So, add the coordinates of the origin to position the planet relative to the center
		   of the screen. */
	double _x_pos = (x_pos / solarSystemRadius) * (origin.x) + origin.x;
	double _y_pos = (y_pos / solarSystemRadius) * (origin.y) + origin.y;
	
	/* Must modify y_pos. In SFML, down is actually the positive y direction. So, for example,
	   in a 10 x 10 window, if the new y coordinate were 2, then the above calculation would be 7
	   (2 above the x axis). However, 7 actually brings it 2 below the x-axis. So, it should be 3
	   because that is 2 above the x-axis. */
	double offset = _y_pos - origin.y;
	_y_pos = origin.y - offset;
	sprite.setPosition(_x_pos, _y_pos);
}


double Planet::forceX(const Planet& planet) const {
	// F = (G)(M1)(M2)/(r^2)
	double deltaX = planet.x_pos - x_pos;
	double deltaY = planet.y_pos - y_pos;
	double radius = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
	double F = G * mass * planet.mass / pow(radius, 2);
	
	// Fx = (F)(deltaX)/(r)
	return F * deltaX / radius;
}


double Planet::forceY(const Planet& planet) const {
	// F = (G)(M1)(M2)/(r^2)
	double deltaX = planet.x_pos - x_pos;
	double deltaY = planet.y_pos - y_pos;
	double radius = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
	double F = G * mass * planet.mass / pow(radius, 2);

	// Fy = (F)(deltay)/(r)
	return F * deltaY / radius;
}


void Planet::setForce(double _x_force, double _y_force) {
	x_force = _x_force;
	y_force = _y_force;
}


void Planet::step(double timeStep) {
	// acceleration = force / mass
	x_accel = x_force / mass;
	y_accel = y_force / mass;

	// new velocity = velocity + (deltaT)(acceleration)
	x_vel += timeStep * x_accel;
	y_vel += timeStep * y_accel;

	// new position = position + (deltaT)(velocity)
	x_pos += timeStep * x_vel;
	y_pos += timeStep * y_vel;

	setPosition();
}


std::ostream& operator<<(std::ostream& output, const Planet& planet) {
	std::ios_base::fmtflags flagSettings = output.flags();	// save output flags
	output.setf(std::ios::left | std::ios::scientific);		// left justified and sci not
	output.precision(4);

	output << std::setw(15) << planet.x_pos << std::setw(15) << planet.y_pos;
	output << std::setw(15) << planet.x_vel << std::setw(15) << planet.y_vel;
	output << std::setw(15) << planet.mass << std::setw(15) << planet.fileName;
	output.flags(flagSettings);
	return output;
}


void Planet::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(sprite, states);
}