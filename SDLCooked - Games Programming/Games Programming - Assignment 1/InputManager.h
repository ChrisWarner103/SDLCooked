#ifndef InputManager_H
#define InputManager_H

#include <SDL.h>
#include <string>
#include "MathHelper.h"
#include "GameEntity.h"

using namespace std;

namespace ChrisFramework {

	class InputManager {

	public:

		enum  MOUSE_BUTTON { left = 0, right, middle, back, forward };

		bool isHolding = false;
		bool hasMeat = false;
		bool hasCheese = false;
		bool hasLettuce = false;
		bool hasBun = false;
		bool hasPlate = false;

	private:

		static InputManager* sInstance;

		Uint8* mPreviousKeyboardState;
		const Uint8* mKeyboardState;
		int mKeyLength;

		Uint32 mPreviousMouseState;
		Uint32 mMouseState;

		int mMousePosX;
		int mMousePosY;

		GameEntity* currentItem;

	public:

		static InputManager* Instance();
		static void Release();

		bool KeyDown(SDL_Scancode scanCode);
		bool KeyPressed(SDL_Scancode scanCode);
		bool KeyReleased(SDL_Scancode scanCode);

		bool MouseButtonDown(MOUSE_BUTTON button);
		bool MouseButtonPressed(MOUSE_BUTTON button);
		bool MouseButtonReleased(MOUSE_BUTTON button);

		Vector2 MousePosition();

		void Update();
		void UpdatePreviousInput();

		GameEntity* GetCurrentHeldItem();
		void SetCurrentHeldItem(GameEntity* entity);

		void DropItem();

	private:

		InputManager();
		~InputManager();

	};
}
#endif // !InputManager_H
