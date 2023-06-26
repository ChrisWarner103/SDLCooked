#ifndef  Graphics_H
#define Graphics_H

#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <string>
#include <SDL_ttf.h>

using namespace std;

namespace ChrisFramework {

	class Graphics {

	public:

		static const int SCREEN_WIDTH = 1280;
		static const int SCREEN_HEIGHT = 720;

		int width, height;

	private:

		static Graphics* sInstance;
		static bool sInitialized;

		SDL_Window* window;
		SDL_Surface* backBuffer;

		SDL_Renderer* mRenderer;

	public:

		static Graphics* Instance();
		static void Release();
		static bool Initalised();

		SDL_Texture* LoadTexture(string path);
		SDL_Texture* CreateTextTexture(TTF_Font* font, string text, SDL_Color color);

		void ClearBackBuffer();

		void DrawTexture(SDL_Texture* texture, SDL_Rect* clip = NULL, SDL_Rect* renderRect = NULL, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);



		void Render();

	private:

		Graphics();
		~Graphics();

		bool Init();
	};
}
#endif // ! Graphics_H

