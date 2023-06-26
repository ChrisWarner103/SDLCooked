#ifndef Buttons_H
#define Buttons_H

#include "StartScreen.h"
#include "InputManager.h"

using namespace ChrisFramework;

class Buttons {

private:

	//Top left point of the button.
	SDL_Point buttonPosition;

public:

	Buttons();
	~Buttons();

	void SetPosition(int x, int y);

	void HandleButtonEvent(SDL_Event* e);

	void Render();

};

#endif // !Buttons_H

