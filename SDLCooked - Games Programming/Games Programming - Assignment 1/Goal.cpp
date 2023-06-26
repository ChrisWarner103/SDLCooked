#include "Goal.h"
#include "ScreenManager.h"
#include "PlateContainer.h"

Goal::Goal()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Level Handout Point Constructed with Param(%p)\n", this);

	mInput = InputManager::Instance();

	goalCounter = new Texture("Environment/Goal.png");
	collider = new Texture("BoxCollider.png");

	goalCounter->Parent(this);
	collider->Parent(this);

	goalCounter->Pos(VEC2_ZERO);
	collider->Pos(Vector2(0.0f, 25.0f));

	collider->Scale(Vector2(2.0f, 1.0f));
}

Goal::~Goal()
{

}

void Goal::CheckRecipe(GameEntity* itemHeld)
{
	RecipeDecider::Instance()->CheckRecipe(itemHeld->ItemName());
}

void Goal::Update()
{
	itemHeld = mInput->GetCurrentHeldItem();

	if ((ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x > (collider->position(world).x - collider->ScaleDimentions().x)) &&
		(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x < (collider->position(world).x + collider->ScaleDimentions().x)) &&
		(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y > (collider->position(world).y - collider->ScaleDimentions().y)) &&
		(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y < (collider->position(world).y + collider->ScaleDimentions().y)))
	{
		ScreenManager::Instance()->returnPlayer()->atGoal = true;
		if (mInput->MouseButtonReleased(mInput->right))
		{
			CheckRecipe(itemHeld);
			itemHeld->Active(false);
			mInput->DropItem();
		}
	}
	else {
		ScreenManager::Instance()->returnPlayer()->atGoal = false;
	}
}

void Goal::Render()
{
	goalCounter->Render();
	//collider->Render();
}
