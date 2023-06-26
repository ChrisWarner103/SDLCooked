#include "FoodContainerCheese.h"
#include "ScreenManager.h"

FoodContainerCheese::FoodContainerCheese()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Cheese Container Constructed with Param(%p)\n", this);

	mInput = InputManager::Instance();

	cheeseContainerTexture = new Texture("/Environment/Storage Cheese.png");
	collsionArea = new Texture("BoxCollider.png");

	cheeseContainerTexture->Pos(VEC2_ZERO);

	collsionArea->Parent(cheeseContainerTexture);
	collsionArea->Pos(Vector2(32.0f, 0.0f));

	collsionArea->Scale(Vector2(0.5f, 1.0f));

	for (int i = 0; i < MAX_AMOUNT_OF_FOOD; i++)
	{
		AddFood();
		foodInContainer++;
	}
}

FoodContainerCheese::~FoodContainerCheese()
{
	for (auto& element : cheeseContainer)
	{
		delete element;
	}
}

void FoodContainerCheese::AddFood()
{
	Cheese* cheese = new Cheese();
	cheese->Parent(cheeseContainerTexture);
	cheese->Active(false);
	cheese->Pos(VEC2_ZERO);
	this->cheeseContainer.push_back(cheese);
}

void FoodContainerCheese::RemoveFood()
{
	cheeseContainer.at(foodInContainer - 1)->Active(true);
	cheeseContainer.at(foodInContainer - 1)->itemNumber = (foodInContainer - 1);
	foodInContainer++;

	AddFood();
}

void FoodContainerCheese::Update()
{
	cheeseContainerTexture->Pos(position(world));

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

	for (int i = 0; i < cheeseContainer.size(); i++)
	{
		if (!cheeseContainer[i]->active())
		{
			cheeseContainer[i]->Pos(Vector2(cheeseContainerTexture->position()));
		}

		if (cheeseContainer[i]->active())
			cheeseContainer[i]->Update();
	}
}

void FoodContainerCheese::Render()
{
	cheeseContainerTexture->Render();

	for (int i = 0; i < cheeseContainer.size(); i++)
	{
		if (cheeseContainer[i]->active())
			cheeseContainer[i]->Render();
	}
}
