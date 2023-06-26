#include "ContainerMeat.h"
#include "ScreenManager.h"

ContainerMeat::ContainerMeat()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Meat Container Constructed with Param(%p)\n", this);

	mInput = InputManager::Instance();

	meatContainerTexture = new Texture("/Environment/Storage Meat.png");
	collsionArea = new Texture("BoxCollider.png");

	meatContainerTexture->Pos(VEC2_ZERO);

	collsionArea->Parent(meatContainerTexture);
	collsionArea->Pos(Vector2(32.0f, 0.0f));

	collsionArea->Scale(Vector2(0.5f, 1.0f));

	for (int i = 0; i < MAX_AMOUNT_OF_FOOD; i++)
	{
		AddFood();
		foodInContainer++;
	}
}

ContainerMeat::~ContainerMeat()
{
	for (auto& element : meatContainer)
	{
		delete element;
	}
}

void ContainerMeat::AddFood()
{
	Meat* meatPatty = new Meat();
	meatPatty->Parent(meatContainerTexture);
	meatPatty->Active(false);
	meatPatty->Pos(VEC2_ZERO);
	this->meatContainer.push_back(meatPatty);
}

void ContainerMeat::RemoveFood()
{
	meatContainer.at(foodInContainer - 1)->Active(true);
	meatContainer.at(foodInContainer - 1)->itemNumber = (foodInContainer - 1);
	foodInContainer++;

	AddFood();
}

void ContainerMeat::Update()
{
	meatContainerTexture->Pos(position(world));

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

	for (int i = 0; i < meatContainer.size(); i++)
	{
		if (!meatContainer[i]->active())
		{
			meatContainer[i]->Pos(Vector2(meatContainerTexture->position()));
		}

		if (meatContainer[i]->active())
			meatContainer[i]->Update();
	}
}

void ContainerMeat::Render()
{
	meatContainerTexture->Render();

	for (int i = 0; i < meatContainer.size(); i++)
	{
		if (meatContainer[i]->active())
			meatContainer[i]->Render();
	}
}
