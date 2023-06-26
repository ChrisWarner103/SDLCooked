#include "GameManager.h"

namespace ChrisFramework {

	GameManager* GameManager::sInstance = NULL;

	GameManager* GameManager::Instance()
	{
		if (sInstance == NULL)
			sInstance = new GameManager();

		return sInstance;
	}

	void GameManager::Release()
	{
		delete sInstance;
		sInstance == NULL;
	}

	GameManager::GameManager() {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Game Manager Constructed with Param(%p)\n", this);

		quit = false;

		graphics = Graphics::Instance();

		//Quit the game if SDL fails to initialize
		if (!Graphics::Initalised())
			quit = true;

		//Initialize Asset Manager
		mAssetManager = AssetManager::Instance();

		//Initialize Input Manager
		mInputManager = InputManager::Instance();

		//Initialize Audio Manager
		mAudioManager = AudioManager::Instance();
		
		//Initialize Timer
		mTimer = Timer::Instance();

		mScreenManager = ScreenManager::Instance();

		//Initialize Physics Manager
		mPhysicsManager = PhysicsManager::Instance();
		mPhysicsManager->SetLayerCollisonMask(PhysicsManager::CollisionLayers::Player, PhysicsManager::CollisionFlags::Food | PhysicsManager::CollisionFlags::Counter | PhysicsManager::CollisionFlags::Plate);
		mPhysicsManager->SetLayerCollisonMask(PhysicsManager::CollisionLayers::Plate, PhysicsManager::CollisionFlags::Food | PhysicsManager::CollisionFlags::Player | PhysicsManager::CollisionFlags::Counter);
		mPhysicsManager->SetLayerCollisonMask(PhysicsManager::CollisionLayers::Food, PhysicsManager::CollisionFlags::Player | PhysicsManager::CollisionFlags::Plate | PhysicsManager::CollisionFlags::Plate);
		mPhysicsManager->SetLayerCollisonMask(PhysicsManager::CollisionLayers::Counter, PhysicsManager::CollisionFlags::Player | PhysicsManager::CollisionFlags::Food | PhysicsManager::CollisionFlags::Plate);

		//Will not need this when done --------------

		mLoadingBar = new Texture("Loading Bar.png");

		mLoadingBar->Pos(Vector2(0.0f, 0.0f));
		mLoadingBar->Scale(Vector2(0.0f, 1.0f));

		//------------------------------------
	}

	GameManager::~GameManager()
	{
		ScreenManager::Release();
		mScreenManager = NULL;

		PhysicsManager::Release();
		mPhysicsManager = nullptr;

		AudioManager::Release();
		mAudioManager = NULL;

		AssetManager::Release();
		mAssetManager = NULL;

		Graphics::Release();
		graphics = NULL;

		InputManager::Release();
		mInputManager = NULL;

		Timer::Release();
		mTimer = NULL;

		delete mLoadingBar;
		mLoadingBar = NULL;
	}

	void GameManager::EarlyUpdate()
	{
		mTimer->Reset();
		mInputManager->Update();
	}

	void GameManager::Update()
	{
		if (mInputManager->KeyReleased(SDL_SCANCODE_M))
		{
			if (!soundsMuted)
			{
				mAudioManager->PauseMusic();
				soundsMuted = true;
			}
			else
			{
				mAudioManager->ResumeMusic();
				soundsMuted = false;
			}
		}

		mScreenManager->Update();
		timer -= mTimer->DeltaTime();

		if (timer >= 0)
			

		if (timer >= 0)
		{
			mLoadingBar->Scale(Vector2((timer / 0.15f) / 100.0f, 1.0f));
		}
	}

	void GameManager::LateUpdate()
	{
		mPhysicsManager->Update();
		mInputManager->UpdatePreviousInput();
	}

	void GameManager::FixedUpdate()
	{

	}

	void GameManager::Render()
	{
		graphics->ClearBackBuffer();

		//All assets that need to be rendered go here. Render order is from front to back.

		mScreenManager->Render();

		//mLoadingBar->Render();

		graphics->Render();
	}

	void GameManager::QuitGame()
	{
		quit = true;
	}

	void GameManager::Run()
	{
		while (!quit)
		{
			mTimer->Update();

			while (SDL_PollEvent(&mEvents))
			{
				if (mEvents.type == SDL_QUIT)
				{
					quit = true;
				}
			}

			if (mTimer->DeltaTime() >= (1.0f / FRAME_RATE))
			{

				EarlyUpdate();
				Update();
				LateUpdate();
				Render();
			}

		}
	}
}