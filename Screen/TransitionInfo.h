//there are transitions from screen to screen
//each screen defines transitionIn and transitionOut times
//the ScreenEngine uses these times to facilitate transitions
//this provides transition info

#ifndef TRANSITIONINFO_H
#define TRANSITIONINFO_H

struct TransitionInfo
{
	bool transitioningIn;
	bool transitioningOut;

	//[0, 1]
	float transitionPercent;
};


#endif



