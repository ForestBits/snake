//holds all types of particles, updates and draws them

#ifndef PARTICLECOLLECTION_H
#define PARTICLECOLLECTION_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "CircleFadeParticle.h"

class ParticleCollection : public sf::Drawable
{
	std::vector<CircleFadeParticle> circleFadeParticles;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
public:
	void update();

	void addParticle(CircleFadeParticle particle);
};




#endif

