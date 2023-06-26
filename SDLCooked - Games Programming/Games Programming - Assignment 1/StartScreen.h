#ifndef StartScreen_H
#define StartScreen_H

#include "AnimatedTexture.h"
#include "InputManager.h"

#include "Scoreboard.h"

using namespace ChrisFramework;

class StartScreen : public GameEntity {

public:

	enum class SCREENSTATE {
		normal,
		options
	};

private:

	//Start screen Entities
	GameEntity* panel;
	Texture* panelBackground;
	Texture* scoreCoin;
	Texture* startIndicator;

	Texture* controlsPanel;
	Texture* closeButton;

	//Play mode Entities
	
	Texture* playButton;
	Texture* optionsButton;
	Texture* exitButton;

	//GameEntity* playPanel;
	//Texture* stopwatch;
	//Texture* timerText;
	//Texture* scoreCoin;
	//Texture* scoreText;

	SCREENSTATE currentScreenState;

public:

	int mouseX, mouseY;
	bool playButtonPressed = false;
	bool optionsButtonPresses = false;

public:

	StartScreen();
	~StartScreen();

	void HandleMouseEvents(SDL_Event* e);

	void Update();

	void Render();
};
#endif // !StartScreen_H
