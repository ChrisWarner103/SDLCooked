#include "Food.h"
#include "ScreenManager.h"

Cheese::Cheese()
{
	mInput = InputManager::Instance();

	mainTexture = new Texture("Food Items/cheese.png");
	choppedTexture = new Texture("Food Items/cheesechopped.png");
	collider = new Texture("BoxCollider.png");

	mainTexture->Parent(this);
	choppedTexture->Parent(this);
	collider->Parent(this);

	mainTexture->Active(false);
	choppedTexture->Active(false);
	collider->Active(false);

	SetItemName("Cheese");

	mainTexture->Scale(Vector2(1.5f, 1.5f));
	choppedTexture->Scale(Vector2(1.5f, 1.5f));
	collider->Scale(Vector2(0.75f, 0.75f));
}

Cheese::~Cheese()
{
	mInput = NULL;

	delete mainTexture;
	mainTexture = NULL;
	delete choppedTexture;
	choppedTexture = NULL;
	delete collider;
	collider = NULL;
}

void Cheese::Update()
{
	Food::Update();

	if (mInput->isHolding) {
		mInput->hasCheese = true;
	}

	if (this->cookingTime >= 15.0f)
	{
		ChangeFoodState(FoodStates::chopped);

		SetItemName("Chopped Cheese");
	}
}
