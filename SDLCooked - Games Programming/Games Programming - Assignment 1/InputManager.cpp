#include "InputManager.h"

namespace ChrisFramework {

	InputManager* InputManager::sInstance = NULL;

	InputManager* InputManager::Instance()
	{
		if (sInstance == NULL)
			sInstance = new InputManager();

		return sInstance;
	}

	void InputManager::Release()
	{
		delete sInstance;

		sInstance = NULL;
	}

	InputManager::InputManager()
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Input Manager Constructed with Param(%p)\n", this);

		mKeyboardState = SDL_GetKeyboardState(&mKeyLength);
		mPreviousKeyboardState = new Uint8[mKeyLength];
		memcpy(mPreviousKeyboardState, mKeyboardState, mKeyLength);
	}

	InputManager::~InputManager()
	{
		delete[] mPreviousKeyboardState;
		mPreviousKeyboardState = NULL;
	}

	bool InputManager::KeyDown(SDL_Scancode scanCode)
	{
		return mKeyboardState[scanCode];
	}

	bool InputManager::KeyPressed(SDL_Scancode scanCode)
	{
		return !mPreviousKeyboardState[scanCode] && mKeyboardState[scanCode];
	}

	bool InputManager::KeyReleased(SDL_Scancode scanCode)
	{
		return mPreviousKeyboardState[scanCode] && !mKeyboardState[scanCode];
	}

	Vector2 InputManager::MousePosition()
	{
		return Vector2((float)mMousePosX, (float)mMousePosY);
	}

	bool InputManager::MouseButtonDown(MOUSE_BUTTON button)
	{
		Uint32 mask = 0;

		switch (button)
		{
		case left:
			mask = SDL_BUTTON_LMASK;
			break;

		case right:
			mask = SDL_BUTTON_RMASK;
			break;

		case middle:
			mask = SDL_BUTTON_MMASK;
			break;

		case back:
			mask = SDL_BUTTON_X1MASK;
			break;

		case forward:
			mask = SDL_BUTTON_X2MASK;
			break;
		}

		return (mMouseState & mask);
	}

	bool InputManager::MouseButtonPressed(MOUSE_BUTTON button)
	{
		Uint32 mask = 0;

		switch (button)
		{
		case left:
			mask = SDL_BUTTON_LMASK;
			break;

		case right:
			mask = SDL_BUTTON_RMASK;
			break;

		case middle:
			mask = SDL_BUTTON_MMASK;
			break;

		case back:
			mask = SDL_BUTTON_X1MASK;
			break;

		case forward:
			mask = SDL_BUTTON_X2MASK;
			break;
		}

		return !(mPreviousMouseState & mask) && (mMouseState & mask);
	}

	bool InputManager::MouseButtonReleased(MOUSE_BUTTON button)
	{
		Uint32 mask = 0;

		switch (button)
		{
		case left:
			mask = SDL_BUTTON_LMASK;
			break;

		case right:
			mask = SDL_BUTTON_RMASK;
			break;

		case middle:
			mask = SDL_BUTTON_MMASK;
			break;

		case back:
			mask = SDL_BUTTON_X1MASK;
			break;

		case forward:
			mask = SDL_BUTTON_X2MASK;
			break;
		}

		return (mPreviousMouseState & mask) && !(mMouseState & mask);
	}



	void InputManager::Update()
	{
		mMouseState = SDL_GetMouseState(&mMousePosX, &mMousePosY);
	}

	void InputManager::UpdatePreviousInput()
	{
		memcpy(mPreviousKeyboardState, mKeyboardState, mKeyLength);
		mPreviousMouseState = mMouseState;
	}
	GameEntity* InputManager::GetCurrentHeldItem()
	{
		return currentItem;
	}
	void InputManager::SetCurrentHeldItem(GameEntity* entity)
	{
		currentItem = entity;
	}
	void InputManager::DropItem()
	{
		SetCurrentHeldItem(NULL);
		isHolding = false;
	}
}