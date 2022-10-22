#include "CelestialBody.h"

CelestialBody::CelestialBody() {}

CelestialBody::CelestialBody(double _x_pos, double _y_pos, double _x_vel, double _y_vel,
	double _mass, double _universeRadius, double _winWidth, double _winHeight,
	const std::string& _fileName) :
	x_pos(_x_pos), y_pos(_y_pos), x_vel(_x_vel), y_vel(_y_vel),
	mass(_mass), universeRadius(_universeRadius), winWidth(_winWidth),
	winHeight(_winHeight), fileName(_fileName) {

	if (!image.loadFromFile(fileName))
		return;

	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setPosition(x_pos, y_pos);
}


void CelestialBody::setRadius(double _universeRadius) {
	universeRadius = _universeRadius;
}


void CelestialBody::setPosition() {
	sf::Vector2u origin(winWidth / 2, winHeight / 2);	// get coordinates of center of window

	/*Instead of using the actual window dimensions, use an
	adjusted dimensions that is 10% smaller (this gives a 5%
	margin going around the border. This prevents a planet
	from being dispalyed partially outside the window. In the
	math that I do below, if I didn't make this adjustment, then
	a planet whose x or y coordinates were the same as the universe
	radius would the be displayed partially out the window*/
	//double adjustedWinWidth = winWidth * 0.9;
	//double adjustedWinHeight = winHeight * 0.9;

	/*Steps to set the position
	- get the ratio of each coordinate to the radius
	- multiply that by half the width/height to get the right proportion
	  of it's x-length or y-length
	- The (0, 0) position in SFML is actually the top left corner and not the
	  center of the screen like in an x-y plane. So, add the coordinates of
	  the origin to position the body relative to the center of the screen*/
	double _x_pos = (x_pos / universeRadius) * (origin.x) + origin.x;
	double _y_pos = (y_pos / universeRadius) * (origin.y) + origin.y;
	
	/* Must modify y_pos. In SFML, down is actually the positive y direction. So, for example,
	   in a 10 x 10 window, if the new y coordinate was 2, then the above calculation would be 7
	   (2 above the x axis). However, 7 actually brings it 2 below the x-axis. So, you actually
	   would want 3 because that is 2 above the x-axis. */
	double offset = _y_pos - origin.y;
	_y_pos = origin.y - offset;
	sprite.setPosition(_x_pos, _y_pos);
}


void CelestialBody::setWindow(double _winWidth, double _winHeight) {
	winWidth = _winWidth;
	winHeight = _winHeight;
}


void CelestialBody::setImage() {
	if (!image.loadFromFile(fileName))
		return;

	texture.loadFromImage(image);
	sprite.setTexture(texture);
	setPosition();
}


double CelestialBody::forceX(const CelestialBody& cBody) const {
	// F = (G)(M1)(M2)/(r^2)
	double deltaX = cBody.x_pos - x_pos;
	double deltaY = cBody.y_pos - y_pos;
	double radius = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
	double F = G * mass * cBody.mass / pow(radius, 2);
	//Fx = (F)(deltaX)/(r)
	return F * deltaX / radius;
}


double CelestialBody::forceY(const CelestialBody& cBody) const {
	// F = (G)(M1)(M2)/(r^2)
	double deltaX = cBody.x_pos - x_pos;
	double deltaY = cBody.y_pos - y_pos;
	double radius = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
	double F = G * mass * cBody.mass / pow(radius, 2);
	//Fx = (F)(deltaX)/(r)
	return F * deltaY / radius;
}


void CelestialBody::setForce(double _x_force, double _y_force) {
	x_force = _x_force;
	y_force = _y_force;
}


void CelestialBody::step(double timeStep) {
	// acceleration = force / mass
	x_accel = x_force / mass;
	y_accel = y_force / mass;
	// new velocity = velocity + (deltaT)(acceleration)
	x_vel += timeStep * x_accel;
	y_vel += timeStep * y_accel;
	// new position = position + (deltaT)(velocity)
	x_pos += timeStep * x_vel;
	y_pos += timeStep * y_vel;
}


std::istream& operator>> (std::istream& input, CelestialBody& cBody) {
	input >> cBody.x_pos >> cBody.y_pos;
	input >> cBody.x_vel >> cBody.y_vel;
	input >> cBody.mass >> cBody.fileName;

	if (!cBody.image.loadFromFile(cBody.fileName)) {
		std::cout << "Failed to load image file named " << cBody.fileName << std::endl;
		return input;
	}

	cBody.texture.loadFromImage(cBody.image);
	cBody.sprite.setTexture(cBody.texture);
	cBody.sprite.setPosition(cBody.x_pos, cBody.y_pos);

	return input;
}


std::ostream& operator<< (std::ostream& output, CelestialBody& cBody) {
	std::ios_base::fmtflags flagSettings = output.flags();	// save output flags
	output.setf(std::ios::left | std::ios::scientific);		// left justified and sci not
	output.precision(4);

	output << std::setw(12) << cBody.x_pos << std::setw(12) << cBody.y_pos;
	output << std::setw(12) << cBody.x_vel << std::setw(12) << cBody.y_vel;
	output << std::setw(12) << cBody.mass << std::setw(12) << cBody.fileName;
	output.flags(flagSettings);
	return output;
}

void CelestialBody::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(sprite);
}
