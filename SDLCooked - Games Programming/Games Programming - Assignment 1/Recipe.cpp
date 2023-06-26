#include "Recipe.h"

Recipe::Recipe()
{
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	cardCreated = false;
}

Recipe::~Recipe()
{
	delete mInput->GetCurrentHeldItem();
}

void Recipe::CreateRecipeCard()
{
	if (recipeType == "Plated Burger Plain")
	{
		recipeCard = new Texture("Recipe/RecipeCardPlain.png");
		recipeTimer = new Texture("Recipe/RecipeTimerBar.png");
		ingredience.push_back(new Texture("Recipe/IngredientMeat.png"));
		ingredience.push_back(new Texture("Recipe/IngredientBun.png"));

		recipeCard->Parent(this);

		recipeTimer->Parent(this);

		recipeTimer->Pos(Vector2(0.0f, -44.5f));

		for (int i = 0; i < ingredience.size(); i++)
		{
			ingredience[i]->Parent(this);
			ingredience[i]->Pos(Vector2((-62.0f * i) + 32.0f, 70.0f));
		}

		cardCreated = true;

		//AddAnimation();
	}

	if (recipeType == "Plated Burger Cheese")
	{

		recipeCard = new Texture("Recipe/RecipeCardCheese.png");
		recipeTimer = new Texture("Recipe/RecipeTimerBar.png");
		ingredience.push_back(new Texture("Recipe/IngredientCheese.png"));
		ingredience.push_back(new Texture("Recipe/IngredientMeat.png"));
		ingredience.push_back(new Texture("Recipe/IngredientBun.png"));

		recipeCard->Parent(this);

		recipeTimer->Parent(this);

		recipeTimer->Pos(Vector2(0.0f, -44.5f));

		for (int i = 0; i < ingredience.size(); i++)
		{
			ingredience[i]->Parent(this);
			ingredience[i]->Pos(Vector2((-62.0f * i) + 64.0f, 70.0f));


		}

		cardCreated = true;

		//AddAnimation();
	}

	if (recipeType == "Plated Burger Lettuce")
	{

		recipeCard = new Texture("Recipe/RecipeCardLettuce.png");
		recipeTimer = new Texture("Recipe/RecipeTimerBar.png");
		ingredience.push_back(new Texture("Recipe/IngredientLettuce.png"));
		ingredience.push_back(new Texture("Recipe/IngredientMeat.png"));
		ingredience.push_back(new Texture("Recipe/IngredientBun.png"));

		recipeCard->Parent(this);

		recipeTimer->Parent(this);

		recipeTimer->Pos(Vector2(0.0f, -44.5f));

		for (int i = 0; i < ingredience.size(); i++)
		{
			ingredience[i]->Parent(this);
			ingredience[i]->Pos(Vector2((-62.0f * i) + 64.0f, 70.0f));
		}

		cardCreated = true;

		//AddAnimation();
	}

	if (recipeType == "Plated Burger Full")
	{
		recipeCard = new Texture("Recipe/RecipeCardFull.png");
		recipeTimer = new Texture("Recipe/RecipeTimerBar.png");
		ingredience.push_back(new Texture("Recipe/IngredientLettuce.png"));
		ingredience.push_back(new Texture("Recipe/IngredientCheese.png"));
		ingredience.push_back(new Texture("Recipe/IngredientMeat.png"));
		ingredience.push_back(new Texture("Recipe/IngredientBun.png"));

		recipeCard->Parent(this);
		recipeTimer->Parent(this);

		recipeTimer->Pos(Vector2(0.0f, -44.5f));

		for (int i = 0; i < ingredience.size(); i++)
		{
			ingredience[i]->Parent(this);
			ingredience[i]->Pos(Vector2((-62.0f * i) + 94.0f, 70.0f));


		}
		cardCreated = true;

		//AddAnimation();

	}
}

void Recipe::CheckRecipeCard()
{
	if (mInput->GetCurrentHeldItem()->itemName == recipeType)
	{
		//mInput->DropItem();
		//RemoveAnimation();
	}
}

float Recipe::ReturnScore()
{
	return recipeScore;
}

void Recipe::AddAnimation()
{
	animationTimer = 0;

	if (!isAnimating)
	{
		animationTimer += mTimer->DeltaTime();
		recipeCard->Pos(Lerp(animationStartPos, animationEndPos, animationTimer / animationTotalTime));

		if (animationTimer >= animationTotalTime)
			isAnimating = true;
	}
}

void Recipe::RemoveAnimation()
{
	animationTimer = 0;

	if (!isAnimating)
	{
		animationTimer += mTimer->DeltaTime();
		recipeCard->Pos(Lerp(animationStartPos, animationEndPos, animationTimer / animationTotalTime));

		if (animationTimer >= animationTotalTime)
			isAnimating = true;
	}
}

void Recipe::UpdatePosition(Vector2 position)
{
	Pos(position);
}

void Recipe::Update()
{
	timeRemaining -= mTimer->DeltaTime();

	if (recipeType == "Plated Burger Plain")
	{
		recipeScore = 500;

		if (timeRemaining < 14)
			recipeScore = 350;
		else if (timeRemaining < 8)
			recipeScore = 250;
	}
	if (recipeType == "Plated Burger Cheese" || recipeType == "Plated Burger Lettuce")
	{
		recipeScore = 750;

		if (timeRemaining < 14)
			recipeScore = 500;
		else if (timeRemaining < 8)
			recipeScore = 375;
	}

	if (recipeType == "Plated Burger Full")
	{
		recipeScore = 1000;

		if (timeRemaining < 14)
			recipeScore = 750;
		else if (timeRemaining < 8)
			recipeScore = 500;
	}


	//if (timeRemaining <= 0)
	//{
	//	RecipeDecider::Instance()->RemoveRecipe(this);
	//	delete this;
	//}
}

void Recipe::Render()
{
	if (cardCreated)
	{
		recipeCard->Render();
		recipeTimer->Render();

		for (int i = 0; i < ingredience.size(); i++)
		{
			ingredience[i]->Render();
		}
	}
}
