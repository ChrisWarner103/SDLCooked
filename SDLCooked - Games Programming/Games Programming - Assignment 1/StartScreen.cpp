#include "StartScreen.h"
#include "GameManager.h"
#include "ScreenManager.h"

StartScreen::StartScreen()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Start Screen Constructed with Param(%p)\n", this);

	panel = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
	panelBackground = new Texture("Start Screen Background.png");
	scoreCoin = new Texture("Coin.png");

	controlsPanel = new Texture("ControllScreen.png");
	closeButton = new Texture("Close Button.png");

	panelBackground->Parent(panel);

	panelBackground->Pos(VEC2_ZERO);

	controlsPanel->Parent(panel);
	closeButton->Parent(panel);

	controlsPanel->Pos(VEC2_ZERO);
	closeButton->Pos(Vector2(120.0f, 220.0f));

	

	//Play mode Entities

	playButton = new Texture("Play Button.png");
	optionsButton = new Texture("Options Button.png");
	exitButton = new Texture("Exit Button.png");

	playButton->Parent(panel);
	optionsButton->Parent(panel);
	exitButton->Parent(panel);

	playButton->Pos(Vector2(-20.0f, 0.0f));
	optionsButton->Pos(Vector2(-20.0f, 100.0f));
	exitButton->Pos(Vector2(-20.0f, 200.0f));

	panel->Parent(this);

	currentScreenState = SCREENSTATE::normal;
}

StartScreen::~StartScreen()
{
	//Freeing UI Entities

	delete panel;
	panel = NULL;
	delete panelBackground;
	panelBackground = NULL;
	delete playButton;
	playButton = NULL;
	delete optionsButton;
	optionsButton = NULL;
	delete exitButton;
	exitButton = NULL;
}

void StartScreen::HandleMouseEvents(SDL_Event* e)
{
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		//Get mouse position
		SDL_GetMouseState(&mouseX, &mouseY);
	}
}

void StartScreen::Update()
{
	InputManager::Instance()->Update();
	mouseX = InputManager::Instance()->MousePosition().x;
	mouseY = InputManager::Instance()->MousePosition().y;

	float scaleX = ((float)Graphics::Instance()->width / Graphics::SCREEN_WIDTH);
	float scaleY = ((float)Graphics::Instance()->height / Graphics::SCREEN_HEIGHT);

	mouseX /= scaleX;
	mouseY /= scaleY;

	switch (currentScreenState)
	{
	case SCREENSTATE::normal:

		if (ScreenManager::Instance()->currentScreen == ScreenManager::SCREENS::start)
		{
			if ((mouseX > (playButton->position(world).x - (174.0f / 2))) && (mouseX < (playButton->position(world).x + (174.0f / 2)))
				&& (mouseY > (playButton->position(world).y - (91.0f / 2))) && (mouseY < (playButton->position(world).y + (91.0f / 2))))
			{
				playButton->Scale(Vector2(0.55f, 0.55f));

				if (InputManager::Instance()->MouseButtonDown(InputManager::left))
				{
					playButton->Scale(Vector2(0.45f, 0.45f));

				}
				else if (InputManager::Instance()->MouseButtonReleased(InputManager::left))
					playButtonPressed = true;
			}
			else
			{
				playButton->Scale(Vector2(0.5f, 0.5f));
			}

			if ((mouseX > (exitButton->position(world).x - (174.0f / 2))) && (mouseX < (exitButton->position(world).x + (174.0f / 2)))
				&& (mouseY > (exitButton->position(world).y - (91.0f / 2))) && (mouseY < (exitButton->position(world).y + (91.0f / 2))))
			{
				exitButton->Scale(Vector2(0.55f, 0.55f));

				if (InputManager::Instance()->MouseButtonDown(InputManager::left))
				{
					exitButton->Scale(Vector2(0.45f, 0.45f));
				}
				else if (InputManager::Instance()->MouseButtonReleased(InputManager::left))
				{
					GameManager::Instance()->QuitGame();
				}
			}
			else
			{
				exitButton->Scale(Vector2(0.5f, 0.5f));
			}

			if ((mouseX > (optionsButton->position(world).x - (174.0f / 2))) && (mouseX < (optionsButton->position(world).x + (174.0f / 2)))
				&& (mouseY > (optionsButton->position(world).y - (91.0f / 2))) && (mouseY < (optionsButton->position(world).y + (91.0f / 2))))
			{
				optionsButton->Scale(Vector2(0.55f, 0.55f));

				if (InputManager::Instance()->MouseButtonDown(InputManager::left))
				{
					optionsButton->Scale(Vector2(0.45f, 0.45f));
				}
				else if (InputManager::Instance()->MouseButtonReleased(InputManager::left))
				{
					currentScreenState = SCREENSTATE::options;
				}
			}
			else
			{
				optionsButton->Scale(Vector2(0.5f, 0.5f));
			}
		}

		break;

	case SCREENSTATE::options:

		if (ScreenManager::Instance()->currentScreen == ScreenManager::SCREENS::start)
		{
			if ((mouseX > (closeButton->position(world).x - (174.0f / 2))) && (mouseX < (closeButton->position(world).x + (174.0f / 2)))
				&& (mouseY > (closeButton->position(world).y - (91.0f / 2))) && (mouseY < (closeButton->position(world).y + (91.0f / 2))))
			{
				closeButton->Scale(Vector2(0.55f, 0.55f));

				if (InputManager::Instance()->MouseButtonDown(InputManager::left))
				{
					closeButton->Scale(Vector2(0.45f, 0.45f));

				}
				else if (InputManager::Instance()->MouseButtonReleased(InputManager::left))
					currentScreenState = SCREENSTATE::normal;
			}
			else
			{
				closeButton->Scale(Vector2(0.5f, 0.5f));
			}
		}

		break;
	}


}

void StartScreen::Render()
{
	panelBackground->Render();

	switch (currentScreenState)
	{
	case SCREENSTATE::normal:

		playButton->Render();
		optionsButton->Render();
		exitButton->Render();

		//scoreCoin->Render();

		break;

	case SCREENSTATE::options:
		
		controlsPanel->Render();
		closeButton->Render();

		break;
	}

}
