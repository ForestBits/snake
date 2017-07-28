#include "ScreenChange.h"
#include "ScreenEngine.h"

ScreenChange::ScreenChange(ScreenEngine * screenEngine) : screenEngine(screenEngine) {}

void ScreenChange::hiddenSetScreen(IScreen * screen)
{
	screenEngine->changeScreen(screen);
}

void ScreenChange::quit()
{
	screenEngine->changeScreen(nullptr);
}