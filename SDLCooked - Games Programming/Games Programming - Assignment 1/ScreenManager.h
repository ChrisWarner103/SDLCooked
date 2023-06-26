#ifndef ScreenManager_H
#define ScreenManager_H

#include "StartScreen.h"
#include "Player.h"
#include "Level.h"

#include "AudioManager.h"

using namespace ChrisFramework;

class ScreenManager {

public:

	enum class SCREENS { start, play, end };

	SCREENS currentScreen;

private:

	static ScreenManager* sInstance;

	InputManager* mInput;
	AudioManager* mAudio;
	RecipeDecider* mRecipeDecider;

	StartScreen *mStartScreen;

	Level* mLevel;

	Player* mPlayer;

public:

	static ScreenManager* Instance();
	static void Release();

	void Update();
	void Render();

	Player* returnPlayer();

private:

	ScreenManager();
	~ScreenManager();

};

#endif // !ScreenManager_H

