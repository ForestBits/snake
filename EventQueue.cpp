#include <assert.h>
#include "EventQueue.h"

EventQueue::EventQueue(sf::RenderWindow & window)
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		events.push_back(event);
	}
}

std::vector<sf::Event>::iterator EventQueue::begin() {return events.begin();}
std::vector<sf::Event>::iterator EventQueue::end() {return events.end();}

bool EventQueue::isEmpty() {return events.empty();}

int EventQueue::getCount() {return events.size();}

sf::Event EventQueue::getEvent(int index)
{
	assert(index >= 0 && index < events.size());

	return events[index];
}