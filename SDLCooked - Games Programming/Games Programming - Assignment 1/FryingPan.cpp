#include "FryingPan.h"

FryingPan::FryingPan()
{
	mInput = InputManager::Instance();
	mTimer = Timer::Instance();

	fryingPan = new Texture("Items/pan.png");
	collider = new Texture("BoxCollider.png");

	hasMeat = false;
	onCooker = false;

	collider->Parent(fryingPan);

	fryingPan->Scale(Vector2(1.5f, 1.5f));
	collider->Scale(Vector2(0.75f, 0.75f));
}

FryingPan::~FryingPan()
{
	mInput = NULL;
	mTimer = NULL;

	delete fryingPan;
	delete collider;

	fryingPan = NULL;
	collider = NULL;
}

void FryingPan::ChangeFoodState(CookingState state)
{

}

void FryingPan::Update()
{
	fryingPan->Pos(position(world));
}

void FryingPan::Render()
{
	fryingPan->Render();
}
