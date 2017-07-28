//SFML's window event polling, by default, gives you the event and pops it off the stack
//this means that event handling can only be done in one location
//this is meant to be taken in one location, and passed to whatever may need the events

#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include <SFML/Graphics.hpp>
#include <vector>

class EventQueue
{
	std::vector<sf::Event> events;

public:
	EventQueue(sf::RenderWindow & window);

	//foreach support
	std::vector<sf::Event>::iterator begin();
	std::vector<sf::Event>::iterator end();

	bool isEmpty();

	int getCount();

	sf::Event getEvent(int index);
};

#endif
