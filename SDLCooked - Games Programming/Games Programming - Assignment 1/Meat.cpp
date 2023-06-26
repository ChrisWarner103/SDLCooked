#include "Food.h"
#include "ScreenManager.h"

Meat::Meat()
{
	mInput = InputManager::Instance();

	mainTexture = new Texture("Food Items/pattyraw.png");
	cookedTexture = new Texture("Food Items/pattycooked.png");
	collider = new Texture("BoxCollider.png");

	mainTexture->Parent(this);
	cookedTexture->Parent(this);
	collider->Parent(this);

	mainTexture->Active(false);
	cookedTexture->Active(false);
	collider->Active(false);

	SetItemName("Meat");

	mainTexture->Scale(Vector2(1.5f, 1.5f));
	cookedTexture->Scale(Vector2(1.5f, 1.5f));
	collider->Scale(Vector2(0.75f, 0.75f));
}

Meat::~Meat()
{
	mInput = NULL;

	delete mainTexture;
	mainTexture = NULL;
	delete cookedTexture;
	cookedTexture = NULL;
	delete collider;
	collider = NULL;
}

void Meat::Update()
{
	Food::Update();

	if (mInput->isHolding) {
		mInput->hasMeat = true;
	}

	if (this->cookingTime >= 5.0f)
	{
		ChangeFoodState(FoodStates::cooked);

		SetItemName("Cooked Meat");
	}
}
