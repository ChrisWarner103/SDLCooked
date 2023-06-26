#include "AnimatedTexture.h"

namespace ChrisFramework {

	AnimatedTexture::AnimatedTexture(string fileName, int x, int y, int w, int h, int frameCount, float animSpeed, ANIM_DIR animDir) : Texture(fileName, x, y, w, h)
	{
		mTimer = Timer::Instance();

		startX = x;
		startY = y;

		mFrameCount = frameCount;
		mAnimSpeed = animSpeed;
		timePerFrame = animSpeed / frameCount;
		animTimer = 0.0f;

		animDirection = animDir;

		animIsDone = false;

		wrapMode = loop;
	}

	AnimatedTexture::~AnimatedTexture()
	{

	}

	void AnimatedTexture::WrapMode(WRAP_MODE mode)
	{
		wrapMode = mode;
	}

	void AnimatedTexture::ResetAnimation()
	{
		animTimer = 0.0f;
		animIsDone = false;
	}

	bool AnimatedTexture::IsAnimating()
	{
		return !animIsDone;
	}

	void AnimatedTexture::Update()
	{
		if (!animIsDone)
		{
			animTimer += mTimer->DeltaTime();

			if (animTimer >= mAnimSpeed)
			{
				if (wrapMode == loop)
				{
					animTimer -= mAnimSpeed;
				}
				else
				{
					animIsDone = true;
					animTimer = mAnimSpeed - timePerFrame;
				}
			}
		}

		if (animDirection == horizontal)
		{
			mClipRect.x = startX + (int)(animTimer / timePerFrame) * width;
		}
		else
		{
			mClipRect.y = startY + (int)(animTimer / timePerFrame) * height;
		}
	}
}