#include "ScreenManager.h"

ScreenManager* ScreenManager::sInstance = NULL;

ScreenManager* ScreenManager::Instance()
{
	if (sInstance == NULL)
		sInstance = new ScreenManager();

	return sInstance;
}

void ScreenManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

ScreenManager::ScreenManager()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Screen Manager Constructed with Param(%p)\n", this);

	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();
	mRecipeDecider = RecipeDecider::Instance();

	mStartScreen = new StartScreen();

	mPlayer = new Player();
	mLevel = new Level(mPlayer);
	
	currentScreen = SCREENS::start;

	

	mPlayer->Pos(Vector2(400.0f, 500.0f));
	mPlayer->Active(true);

	mAudio->PlayMusic("/Music/TitleScreenMusic.wav", 0);
}

ScreenManager::~ScreenManager()
{
	mInput = NULL;

	delete mPlayer;
	mPlayer = NULL;

	delete mStartScreen;
	mStartScreen = NULL;

	delete mLevel;
	mLevel = NULL;

	RecipeDecider::Release();
	mRecipeDecider = NULL;
}

void ScreenManager::Update()
{
	switch (currentScreen)
	{
	case SCREENS::start:

		if (mStartScreen->playButtonPressed)
		{
			currentScreen = SCREENS::play;
		}

		mStartScreen->Update();

		break;

	case SCREENS::play:

		if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE))
		{
			mStartScreen->playButtonPressed = false;
			currentScreen = SCREENS::start;
		}

		mPlayer->Update();
		mLevel->Update();
		mRecipeDecider->Update();
		break;

	case SCREENS::end:

		mLevel->Update();

		break;
	}
}

void ScreenManager::Render()
{
	switch (currentScreen) {

	case SCREENS::start:

		//Render Start Screen
		mStartScreen->Render();

		break;

	case SCREENS::play:
		//Render Play Screen

		mLevel->Render();

		mPlayer->Render();

		mRecipeDecider->Render();

		break;

	case SCREENS::end:
		mLevel->Render();
		break;
	}
}

Player* ScreenManager::returnPlayer()
{
	return mPlayer;
}