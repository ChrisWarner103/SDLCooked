#include "Graphics.h"

namespace ChrisFramework {

	Graphics* Graphics::sInstance = NULL;
	bool Graphics::sInitialized = false;

	Graphics* Graphics::Instance()
	{
		if (sInstance == NULL)
			sInstance = new Graphics();

		return sInstance;
	}

	void Graphics::Release()
	{
		delete sInstance;
		sInstance = NULL;

		sInitialized = false;
	}

	bool Graphics::Initalised()
	{
		return sInitialized;
	}

	Graphics::Graphics()
	{
		backBuffer = NULL;

		sInitialized = Init();

		SDL_GetWindowSize(window, &width, &height);
	}

	Graphics::~Graphics()
	{
		SDL_DestroyWindow(window);
		window = NULL;

		SDL_DestroyRenderer(mRenderer);
		mRenderer = NULL;

		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}

	bool Graphics::Init()
	{
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		{
			printf("SDL Initialization Error: %s\n", SDL_GetError());
			return false;
		}

		window = SDL_CreateWindow("Christopher Warner; CGP2015M Games Programming; 17668933; SDLCooked!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (window == NULL)
		{
			printf("Window Creation Error: %s\n", SDL_GetError());
			return false;
		}

		mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		if (mRenderer == NULL)
		{
			printf("Renderer Creation Error: %s\n", SDL_GetError());
			return false;
		}

		SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

		int flags = IMG_INIT_PNG;
		if (!(IMG_Init(flags) & flags))
		{
			printf("IMG Initialization Error: %s\n", IMG_GetError());
			return false;
		}

		if (TTF_Init() == -1)
		{
			printf("TTF Initialization Error: %s\n", TTF_GetError());
			return false;
		}

		backBuffer = SDL_GetWindowSurface(window);

		return true;
	}

	SDL_Texture* Graphics::LoadTexture(string path)
	{
		SDL_Texture* texture = NULL;

		SDL_Surface* surface = IMG_Load(path.c_str());
		if (surface == NULL)
		{
			printf("Image Load Error: Path(%s) - Error(%s)\n", path.c_str(), IMG_GetError());
			return texture;
		}

		texture = SDL_CreateTextureFromSurface(mRenderer, surface);
		if (texture == NULL)
		{
			printf("Create Texture Error: %s\n", SDL_GetError());
			return texture;
		}

		SDL_FreeSurface(surface);

		return texture;

	}

	SDL_Texture* Graphics::CreateTextTexture(TTF_Font* font, string text, SDL_Color color)
	{
		SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);

		if (surface == NULL)
		{
			printf("Text Render Error: %s\n", TTF_GetError());
			return NULL;
		}

		SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);

		if (texture == NULL)
		{
			printf("Text Texture Creation Error: %s\n", SDL_GetError());
			return NULL;
		}

		SDL_FreeSurface(surface);

		return texture;
	}

	void Graphics::ClearBackBuffer()
	{
		SDL_RenderClear(mRenderer);
	}

	void Graphics::DrawTexture(SDL_Texture* tex, SDL_Rect* clip, SDL_Rect* renderRect, float angle, SDL_RendererFlip flip)
	{
		SDL_RenderCopyEx(mRenderer, tex, clip, renderRect, angle, NULL, flip);
	}

	void Graphics::Render()
	{
		SDL_RenderPresent(mRenderer);
	}
}