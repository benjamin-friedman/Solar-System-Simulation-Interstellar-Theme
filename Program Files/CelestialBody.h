#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>
#include <cmath>
#include <iomanip>

class CelestialBody : public sf::Drawable
{
public:
	//Constructors
	CelestialBody();
	CelestialBody(double _x_pos, double _y_pos, double _x_vel, double _y_vel,
		double _mass, double _universeRadius, double _winWidth, double _winHeight,
		const std::string& _fileName);

	// Setters
	
	/* Sets the radius */
	void setRadius(double _universeRadius);
	
	/* Coordinates x_pos and y_pos are for a regular x-y plane with the origin
	   at the center of the screen. SFML origin (0, 0) is actually the top left
	   corner so this function adjusts the actual coordinates of the sprite to
	   account for this. This function must be called after reading body info
	   from >> or anytime x_pos and y_pos change*/
	void setPosition();
	
	/* sets the window's height and width so the body can know the dimensions of
	   the window it's in*/
	void setWindow(double _winWidth, double _winHeight);
	
	/* Takes a "fileName" and makes the image, texture, and sprite from it.
	   Also calls setPosition. I never actually use this in this program
	   since >> already does this*/
	void setImage();
	
	/* Set the x-y force components */
	void setForce(double _x_force, double _y_force);
	
	/* Initiates a single time step. Updates the x-y coordinates, velocity, and image
	   position. setForce must have been called before this to update the force components
	   since all these calculations are based on the force components. timeStep was
	   passed as on of the command line arguments*/
	void step(double timeStep);


	// Getters
	/* Returns the radius */
	double getRadius() const { return universeRadius; }
	
	/* Returns the mass */
	double getMass() const { return mass; }

	// Other
	/* returns the x and y forces between calling object and cBody */
	double forceX(const CelestialBody& cBody) const;
	double forceY(const CelestialBody& cBody) const;
	
	// input x-y coordinates, mass, universe radius, and image file name
	friend std::istream& operator>>(std::istream& input, CelestialBody& cBody);
	
	//outputs x-y coordinates, mass, universe radius, and image file name
	friend std::ostream& operator<<(std::ostream& output, CelestialBody& cBody);

	static constexpr double G = 6.67e-11;
private:

	// draw
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	// info about celestial body
	double x_pos, y_pos;	// x and y position
	double x_vel, y_vel;	// x and y velocity
	double x_force, y_force;	// x and y force components
	double x_accel, y_accel;	// x and y acceleration
	double mass;	    // mass of body
	double universeRadius;  // radius of universe
	double winWidth, winHeight; // size of the window it will be displayed in
	std::string fileName;   // file containing body image


	// image objects
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
};
