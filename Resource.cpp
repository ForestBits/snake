#include "Resource.h"
#include "Exception.h"

Resource::Resource()
{
	if (!font.loadFromFile("res/Jet Set.ttf"))
		throw Exception(Cause::MISSING_FONT_FILE);

	if (!clickSoundBuffer.loadFromFile("res/clickSound.wav"))
		throw Exception(Cause::MISSING_CLICK_SOUND);

	if (!foodSoundBuffer.loadFromFile("res/foodSound.wav"))
		throw Exception(Cause::MISSING_FOOD_SOUND);

	if (!deathSoundBuffer.loadFromFile("res/deathSound.wav"))
		throw Exception(Cause::MISSING_DEATH_SOUND);

	if (!pauseSoundBuffer.loadFromFile("res/pauseSound.wav"))
		throw Exception(Cause::MISSING_PAUSE_SOUND);

	if (!icon.loadFromFile("res/icon.png"))
		throw Exception(Cause::MISSING_ICON_IMAGE);

	if (!sfmlLogo.loadFromFile("res/sfml.png"))
		throw Exception(Cause::MISSING_SFML_IMAGE);
}

const sf::Font & Resource::getFont() {return font;}
const sf::SoundBuffer & Resource::getClickSoundBuffer() {return clickSoundBuffer;}
const sf::SoundBuffer & Resource::getFoodSoundBuffer() {return foodSoundBuffer;}
const sf::SoundBuffer & Resource::getDeathSoundBuffer() {return deathSoundBuffer;}
const sf::SoundBuffer & Resource::getPauseSoundBuffer() {return pauseSoundBuffer;}
const sf::Image & Resource::getIcon() {return icon;}
const sf::Image & Resource::getSfmlLogo() {return sfmlLogo;}