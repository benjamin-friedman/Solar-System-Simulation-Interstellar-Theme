#include "Universe.h"


Universe::Universe() {}


void Universe::addBody(std::unique_ptr<CelestialBody>  &cBody) {
	cBodies.push_back(std::move(cBody));
}


const std::unique_ptr<CelestialBody>& Universe::getBody(int index) const {
	return cBodies[index];
}


int Universe::getNumBodies() const {
	return cBodies.size();
}
