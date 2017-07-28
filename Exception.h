#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>

enum class Cause
{
	MISSING_FONT_FILE,
	MISSING_CLICK_SOUND,
	MISSING_FOOD_SOUND,
	MISSING_DEATH_SOUND,
	MISSING_PAUSE_SOUND,
	MISSING_MENU_MUSIC,
	MISSING_GAME_MUSIC,
	MISSING_ICON_IMAGE,
	MISSING_SFML_IMAGE
};

class Exception : public std::runtime_error
{
	Cause cause;

	std::string getAsString(Cause cause)
	{
		switch (cause)
		{
		case Cause::MISSING_FONT_FILE:
			return "Missing font file \"Jet Set.ttf\"";

			break;

		case Cause::MISSING_CLICK_SOUND:
			return "Missing click sound \"clickSound.wav\"";

			break;

		case Cause::MISSING_FOOD_SOUND:
			return "Missing food sound \"foodSound.wav\"";

			break;

		case Cause::MISSING_DEATH_SOUND:
			return "Missing death sound \"deathSound.wav\"";

			break;

		case Cause::MISSING_PAUSE_SOUND:
			return "Missing pause sound \"pauseSound.wav\"";

			break;

		case Cause::MISSING_MENU_MUSIC:
			return "Missing menu music \"Pamgaea.ogg\"";

			break;

		case Cause::MISSING_GAME_MUSIC:
			return "Missing game music \"Electrodoodle.ogg\"";

			break;

		case Cause::MISSING_ICON_IMAGE:
			return "Missing icon image \"icon.png\"";

			break;

		case Cause::MISSING_SFML_IMAGE:
			return "Missing sfml logo image \"sfml.png\"";

			break;
		}
	}

public:
	Exception(Cause cause) : cause(cause), std::runtime_error(getAsString(cause)) 
	{
	
	}

	Cause getCause() 
	{
		return cause;
	}
};

#endif
