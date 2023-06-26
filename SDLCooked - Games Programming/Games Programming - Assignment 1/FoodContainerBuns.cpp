#include "FoodContainerBuns.h"
#include "ScreenManager.h"

FoodContainerBuns* FoodContainerBuns::sInstance = NULL;

FoodContainerBuns* FoodContainerBuns::Instance()
{
	if (sInstance == NULL)
		sInstance = new FoodContainerBuns();

	return sInstance;
}

void FoodContainerBuns::Release()
{
	delete sInstance;
	sInstance == NULL;
}

FoodContainerBuns::FoodContainerBuns()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Bun Container Constructed with Param(%p)\n", this);

	mInput = InputManager::Instance();

	bunContainerTexture = new Texture("/Environment/Storage Buns.png");
	collsionArea = new Texture("BoxCollider.png");

	bunContainerTexture->Pos(VEC2_ZERO);

	collsionArea->Parent(bunContainerTexture);
	collsionArea->Pos(Vector2(32.0f, 0.0f));

	collsionArea->Scale(Vector2(0.5f, 1.0f));

	for (int i = 0; i < MAX_AMOUNT_OF_FOOD; i++)
	{
		AddFood();
		foodInContainer++;
	}
}

FoodContainerBuns::~FoodContainerBuns()
{
	for (auto& element : bunsContainer)
	{
		delete element;
	}
}

void FoodContainerBuns::AddFood()
{
	Bun* bun = new Bun();
	bun->Parent(bunContainerTexture);
	bun->Active(false);
	bun->Pos(VEC2_ZERO);
	this->bunsContainer.push_back(bun);
}

void FoodContainerBuns::RemoveFood()
{
	bunsContainer.at(foodInContainer - 1)->Active(true);
	bunsContainer.at(foodInContainer - 1)->itemNumber = (foodInContainer - 1);
	foodInContainer++;

	AddFood();
}

void FoodContainerBuns::RemoveBunFromList(int itemNumber)
{
	bunsContainer.erase(bunsContainer.begin() + itemNumber);
}

void FoodContainerBuns::Update()
{
	bunContainerTexture->Pos(position(world));

	if (bunsContainer.size() < foodInContainer)
	{
		foodInContainer = bunsContainer.size();
	}

	if ((ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x > (collsionArea->position().x - collsionArea->ScaleDimentions().x)) &&
		(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x < (collsionArea->position().x + collsionArea->ScaleDimentions().x)) &&
		(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y > (collsionArea->position().y - collsionArea->ScaleDimentions().y)) &&
		(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y < (collsionArea->position().y + collsionArea->ScaleDimentions().y)))
	{
		if (mInput->KeyPressed(SDL_SCANCODE_E))
		{
			RemoveFood();
		}
	}

	for (int i = 0; i < bunsContainer.size(); i++)
	{
		if (!bunsContainer[i]->active())
		{
			bunsContainer[i]->Pos(Vector2(bunContainerTexture->position()));
		}

		if (bunsContainer[i]->active())
			bunsContainer[i]->Update();
	}
}

void FoodContainerBuns::Render()
{
	bunContainerTexture->Render();

	for (int i = 0; i < bunsContainer.size(); i++)
	{
		if (bunsContainer[i]->active())
			bunsContainer[i]->Render();
	}
}
