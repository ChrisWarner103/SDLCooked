#include "Texture.h"

namespace ChrisFramework {

	Texture::Texture(string fileName)
	{
		mGraphics = Graphics::Instance();

		mTexture = AssetManager::Instance()->GetTexture(fileName);

		SDL_QueryTexture(mTexture, NULL, NULL, &width, &height);

		clipped = false;

		mRenderRect.w = width;
		mRenderRect.h = height;

		velocity.x = 0.0f;
		velocity.y = 0.0f;
	}

	Texture::Texture(string fileName, int x, int y, int w, int h)
	{
		mGraphics = Graphics::Instance();

		mTexture = AssetManager::Instance()->GetTexture(fileName);

		clipped = true;

		width = w;
		height = h;

		mRenderRect.w = width;
		mRenderRect.h = height;

		mClipRect.x = x;
		mClipRect.y = y;
		mClipRect.w = width;
		mClipRect.h = height;

		velocity.x = 0.0f;
		velocity.y = 0.0f;
	}

	Texture::Texture(string text, string fontPath, int size, SDL_Color color)
	{
		mGraphics = Graphics::Instance();

		mTexture = AssetManager::Instance()->GetText(text, fontPath, size, color);

		clipped = false;

		SDL_QueryTexture(mTexture, NULL, NULL, &width, &height);

		mRenderRect.w = width;
		mRenderRect.h = height;

		velocity.x = 0.0f;
		velocity.y = 0.0f;
	}

	Texture::~Texture()
	{
		mTexture = NULL;
		mGraphics = NULL;
	}

	Vector2 Texture::ScaleDimentions()
	{
		Vector2 scaleDimentions = scale(world);
		scaleDimentions.x *= width;
		scaleDimentions.y *= height;
		
		return scaleDimentions;
	}

	void Texture::Render()
	{
		Vector2 pos = position(world);
		Vector2 scale1 = scale(world);

		mRenderRect.x = (int)(pos.x - width * scale1.x * 0.5f);
		mRenderRect.y = (int)(pos.y - height * scale1.y * 0.5f);

		mRenderRect.w = (int)(width * scale1.x);
		mRenderRect.h = (int)(height * scale1.y);

		mGraphics->DrawTexture(mTexture, (clipped) ? &mClipRect : NULL, &mRenderRect, rotation(world));
	}

	void Texture::Update()
	{
		velocity.y = velocity.y + 1;

		if (GameEntity::position(world).y >= 550)
		{
			velocity.y = -15;
		}

		GameEntity::Pos(Vector2(GameEntity::position(world).x + velocity.x, GameEntity::position(world).y + velocity.y));
	}
}