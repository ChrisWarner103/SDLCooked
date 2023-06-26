#include "RecipeDecider.h"
#include "PlateContainer.h"
#include "FoodContainerBuns.h"
#include "RecipeDecider.h"

RecipeDecider* RecipeDecider::sInstance = NULL;
Player* RecipeDecider::sPlayer = nullptr;

RecipeDecider* RecipeDecider::Instance()
{
	if (sInstance == NULL)
		sInstance = new RecipeDecider();

	return sInstance;
}

void RecipeDecider::Release()
{
	delete sInstance;
	sInstance = NULL;
}

void RecipeDecider::CurrentPlayer(Player* player)
{
	sPlayer = player;
}

RecipeDecider::RecipeDecider()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Recipe Decider Constructed with Param(%p)\n", this);

	mInput = InputManager::Instance();
}

RecipeDecider::~RecipeDecider()
{
	mRecipeDecider = NULL;

	for (auto& element : listOfRecipes)
	{
		delete element;
	}
}

void RecipeDecider::ChooseRecipe()
{
	int randomNumber;

	randomNumber = rand() % 4 + 1;

	if (randomNumber == 1) // Normal plain burger
	{
		Recipe* recipe = new Recipe();
		recipe->recipeType = "Plated Burger Plain";
		recipe->CreateRecipeCard();
		listOfRecipes.push_back(recipe);
	}
	if (randomNumber == 2) // Burger with Cheese
	{
		Recipe* recipe = new Recipe();
		recipe->recipeType = "Plated Burger Cheese";
		recipe->CreateRecipeCard();
		listOfRecipes.push_back(recipe);
	}
	if (randomNumber == 3) // Burger with Lettuce
	{
		Recipe* recipe = new Recipe();
		recipe->recipeType = "Plated Burger Lettuce";
		recipe->CreateRecipeCard();
		listOfRecipes.push_back(recipe);
	}
	if (randomNumber == 4) //Burger with all the above
	{
		Recipe* recipe = new Recipe();
		recipe->recipeType = "Plated Burger Full";
		recipe->CreateRecipeCard();
		listOfRecipes.push_back(recipe);
	}
}

void RecipeDecider::CheckRecipe(string type)
{
	for (int i = 0; i < listOfRecipes.size(); i++)
	{
		if (mInput->isHolding)
		{
			if (listOfRecipes[i]->recipeType == type)
			{
				listOfRecipes[i]->CheckRecipeCard();
				currentScore = listOfRecipes[i]->ReturnScore();
				sPlayer->AddScore(currentScore);

				FoodContainerBuns::Instance()->RemoveBunFromList(mInput->GetCurrentHeldItem()->itemNumber);
				PlateContainer::Instance()->RemovePlateFromList(mInput->GetCurrentHeldItem()->itemNumber);
				mInput->DropItem();

				delete listOfRecipes[i];
				listOfRecipes.erase(listOfRecipes.begin() + i);
			}
		}
	}
}

void RecipeDecider::RemoveRecipe(Recipe* object) {
	
	//delete listOfRecipes.
}

void RecipeDecider::Update()
{
	if (listOfRecipes.empty())
		ChooseRecipe();

	if (listOfRecipes.size() < maxAmountOfRecipes)
		if (nextRecipeTimer <= 0)
		{
			ChooseRecipe();
			nextRecipeTimer = 10;
		}
		else
		{
			nextRecipeTimer -= Timer::Instance()->DeltaTime();
		}

	for (int i = 0; i < listOfRecipes.size(); i++)
	{
		if (i == 0)
		{
			listOfRecipes[i]->UpdatePosition(Vector2((125.0f * (i + 1)), 75.0f));
		}
		else
		{
			listOfRecipes[i]->UpdatePosition(Vector2((250.0f * i) + 125.0f, 75.0f));
		}

		listOfRecipes[i]->Update();
	}
}

void RecipeDecider::Render()
{
	for (int i = 0; i < listOfRecipes.size(); i++)
	{
		listOfRecipes[i]->Render();
	}
}
