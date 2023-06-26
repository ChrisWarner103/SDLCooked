#include "AssetManager.h"

namespace ChrisFramework {

	AssetManager* AssetManager::sInstance = NULL;

	AssetManager* AssetManager::Instance()
	{
		if (sInstance == NULL)
			sInstance = new AssetManager();

		return sInstance;
	}

	void AssetManager::Release()
	{
		delete sInstance;
		sInstance = NULL;
	}

	AssetManager::AssetManager()
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Asset Manager Constructed with Param(%p)\n", this);
	}

	AssetManager::~AssetManager()
	{
		for (auto texture : mTexture)
		{
			if (texture.second != NULL)
			{
				SDL_DestroyTexture(texture.second);
			}
		}

		mTexture.clear();

		for (auto text : mText)
		{
			if (text.second != NULL)
			{
				SDL_DestroyTexture(text.second);
			}
		}

		mText.clear();

		for (auto font : mFonts)
		{
			if (font.second != NULL)
			{
				TTF_CloseFont(font.second);
			}
		}

		mFonts.clear();

		for (auto music : mMusic)
		{
			if (music.second != NULL)
			{
				Mix_FreeMusic(music.second);
			}
		}

		mMusic.clear();

		for (auto sfx : mSFX)
		{
			if (sfx.second != NULL)
			{
				Mix_FreeChunk(sfx.second);
			}
		}

		mSFX.clear();
	}

	SDL_Texture* AssetManager::GetTexture(string fileName)
	{
		string fullPath = SDL_GetBasePath();
		fullPath.append("Content/" + fileName);

		if (mTexture[fullPath] == nullptr)
			mTexture[fullPath] = Graphics::Instance()->LoadTexture(fullPath);

		return mTexture[fullPath];

	}

	TTF_Font* AssetManager::GetFont(string fileName, int size)
	{
		string fullPath = SDL_GetBasePath();
		fullPath.append("Content/" + fileName);
		string key = fullPath + (char)size;

		if (mFonts[key] == nullptr)
		{
			mFonts[key] = TTF_OpenFont(fullPath.c_str(), size);
			if (mFonts[key] == nullptr)
			{
				printf("Font Loading Error: Font - %s Error - %s\n", fileName.c_str(), TTF_GetError());
			}
		}

		return mFonts[key];
	}

	SDL_Texture* AssetManager::GetText(string text, string fileName, int size, SDL_Color color)
	{
		TTF_Font* font = GetFont(fileName, size);

		string key = text + fileName + (char)size + (char)color.r + (char)color.b + (char)color.g;

		if (mText[key] == nullptr)
		{
			mText[key] = Graphics::Instance()->CreateTextTexture(font, text, color);
		}

		return mText[key];
	}

	Mix_Music* AssetManager::GetMusic(string fileName)
	{
		string fullPath = SDL_GetBasePath();

		fullPath.append("Content/" + fileName);

		if (mMusic[fullPath] == nullptr)
		{
			mMusic[fullPath] = Mix_LoadMUS(fullPath.c_str());

			if (mMusic[fullPath] == NULL)
			{
				printf("Music Loading Error: File - %s Error - %s\n", fileName.c_str(), Mix_GetError());
			}
		}

		return mMusic[fullPath];
	}

	Mix_Chunk* AssetManager::GetSFX(string fileName)
	{

		//Get the full path of the WAV file
		std::string fullPath = SDL_GetBasePath();
		fullPath.append("Content/" + fileName);

		//If the file has not been already loaded, load it and add it to the mSFX map
		if (mSFX[fullPath] == nullptr) {

			mSFX[fullPath] = Mix_LoadWAV(fullPath.c_str());
			//Error handling for file loading
			if (mSFX[fullPath] == NULL)
				printf("SFX Loading Error: File - %s Error - %s\n", fileName.c_str(), Mix_GetError());
		}

		//returning the cached file from the map
		return mSFX[fullPath];
	}
}