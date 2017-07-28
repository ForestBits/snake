//allows changing screen, while protecting the engine (so screens cannot call update(), etc)

#ifndef SCREENCHANGE_H
#define SCREENCHANGE_H

class ScreenEngine;
class IScreen;

class ScreenChange
{
	ScreenEngine * screenEngine;


	void hiddenSetScreen(IScreen * screen);
public:
	ScreenChange(ScreenEngine * screenEngine);

	template <typename T, typename... Args>
	void setScreen(Args && ... args )
	{
		hiddenSetScreen(new T(args...));
	}

	//call to quit the program
	void quit();
};

#endif
