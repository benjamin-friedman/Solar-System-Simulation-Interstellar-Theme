#pragma once

#include "CelestialBody.h"
#include <vector>
#include <memory>

class Universe
{
public:
	Universe();

	void addBody(std::unique_ptr<CelestialBody> &cBody);
	const std::unique_ptr<CelestialBody>& getBody(int index) const;
	int getNumBodies() const;
private:
	std::vector<std::unique_ptr<CelestialBody>> cBodies;
};
