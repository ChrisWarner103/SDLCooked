#include "FoodContainerLettuce.h"
#include "ScreenManager.h"

FoodContainerLettuce::FoodContainerLettuce()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Lettuce Container Constructed with Param(%p)\n", this);

	mInput = InputManager::Instance();

	lettuceContainerTexture = new Texture("/Environment/Storage Lettuce.png");
	collsionArea = new Texture("BoxCollider.png");

	lettuceContainerTexture->Pos(VEC2_ZERO);

	collsionArea->Parent(lettuceContainerTexture);
	collsionArea->Pos(Vector2(32.0f, 0.0f));

	collsionArea->Scale(Vector2(0.5f, 1.0f));

	for (int i = 0; i < MAX_AMOUNT_OF_FOOD; i++)
	{
		AddFood();
		foodInContainer++;
	}
}

FoodContainerLettuce::~FoodContainerLettuce()
{
	for (auto& element : lettuceContainer)
	{
		delete element;
	}
}

void FoodContainerLettuce::AddFood()
{
	Lettuce* lettuce = new Lettuce();
	lettuce->Parent(lettuceContainerTexture);
	lettuce->Active(false);
	lettuce->Pos(VEC2_ZERO);
	this->lettuceContainer.push_back(lettuce);
}

void FoodContainerLettuce::RemoveFood()
{
	lettuceContainer.at(foodInContainer - 1)->Active(true);
	lettuceContainer.at(foodInContainer - 1)->itemNumber = (foodInContainer - 1);
	foodInContainer++;

	AddFood();
}

void FoodContainerLettuce::Update()
{
	lettuceContainerTexture->Pos(position(world));

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

	for (int i = 0; i < lettuceContainer.size(); i++)
	{
		if (!lettuceContainer[i]->active())
		{
			lettuceContainer[i]->Pos(Vector2(lettuceContainerTexture->position()));
		}

		if (lettuceContainer[i]->active())
			lettuceContainer[i]->Update();
	}
}

void FoodContainerLettuce::Render()
{
	lettuceContainerTexture->Render();

	for (int i = 0; i < lettuceContainer.size(); i++)
	{
		if (lettuceContainer[i]->active())
			lettuceContainer[i]->Render();
	}
}
