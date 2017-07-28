#include "ParticleCollection.h"

void ParticleCollection::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (auto particle : circleFadeParticles)
		target.draw(particle);
}

void ParticleCollection::update()
{
	std::vector<CircleFadeParticle> circleFadeParticlesToRemove;

	for (auto & particle : circleFadeParticles)
	{
		if (particle.clock.getElapsedTime().asSeconds() >= particle.lifeSpan)
		{
			circleFadeParticlesToRemove.push_back(particle);

			continue;
		}

		particle.radius += 1;
	}

	for (auto toRemove : circleFadeParticlesToRemove)
		circleFadeParticles.erase(std::find(circleFadeParticles.begin(), circleFadeParticles.end(), toRemove));
}

void ParticleCollection::addParticle(CircleFadeParticle particle) {circleFadeParticles.push_back(particle);}