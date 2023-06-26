#ifndef GameManager_H
#define GameManager_H

#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "PhysicsManager.h"
#include "ScreenManager.h"
#include "ScreenManager.h"
#include "RecipeDecider.h"

namespace ChrisFramework {

	class GameManager
	{
	private:

		static GameManager* sInstance;

		const int FRAME_RATE = 60;
		float timer = 120.0f;

		bool quit;
		Graphics* graphics;
		AssetManager* mAssetManager;
		InputManager* mInputManager;
		AudioManager* mAudioManager;
		PhysicsManager* mPhysicsManager;
		ScreenManager* mScreenManager;

		Timer* mTimer;

		SDL_Event mEvents;

		Texture* mTexture;
		Texture* mTexture2;
		Texture* mTexture3;

		Texture* mLoadingBar;

		GameEntity* mParent;
		GameEntity* mChild;

		float speedX = 40.0f, speedY = 40.0f;

	public:

		bool soundsMuted = false;

	public:

		static GameManager* Instance();
		static void Release();

		void Run();

		void QuitGame();

	private:

		GameManager();
		~GameManager();

		void EarlyUpdate();
		void Update();
		void LateUpdate();
		void FixedUpdate();

		void Render();

		
	};

}
#endif // !GameManager_H

