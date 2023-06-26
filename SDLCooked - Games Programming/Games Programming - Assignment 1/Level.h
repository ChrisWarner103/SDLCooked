#ifndef Level_H
#define Level_H

#include <iomanip>
#include <sstream>

#include "InputManager.h"
#include "GameEntity.h"
#include "AnimatedTexture.h"

#include "Scoreboard.h"

#include "ContainerMeat.h"
#include "FoodContainerCheese.h"
#include "FoodContainerBuns.h"
#include "FoodContainerLettuce.h"
#include "PlateContainer.h"

#include "Cooker.h"
#include "Chopping.h"

#include "Goal.h"

#include "RecipeDecider.h"


using namespace ChrisFramework;

class Level {

public:

	enum class LEVELSTATES {
		playing,
		finished

	};

private:

	Timer* mTimer;
	InputManager* mInput;
	RecipeDecider* mRecipeDecider;

	Player* mPlayer;

	Chopping* choppingStation1;
	Chopping* choppingStation2;
	Chopping* choppingStation3;
	Chopping* choppingStation4;

	//Cookers
	Cooker* cooker1;
	Cooker* cooker2;
	Cooker* cooker3;
	Cooker* cooker4;
	Cooker* cooker5;

	//Food Crates
	FoodContainerCheese* cheeseCrate;
	ContainerMeat* meatCrate;
	FoodContainerLettuce* lettuceCrate;
	FoodContainerBuns* bunCrate;
	PlateContainer* plateCrate;

	Texture* counter1;
	Texture* counter2;
	Texture* counter3;
	Texture* counter4;
	Texture* counter5;

	Texture* levelFloor;

	Goal* resturantOutgoing;

	Texture* endLevelScreen;

	Texture* exitButton;

	//UI
	Texture* stopWatch;
	Texture* scoreCoin;
	Scoreboard* playerScore;
	Scoreboard* countDownTimer;

	float timer = 150.0f;
	int playerTotalScore;

	LEVELSTATES currentLevelState;

public:

	Level(Player* player);
	~Level();

	void SetPlayerScore(int score);

	void Update();
	void UpdateTimer();
	
	void AssignPlayer(Player* player);

	void Render();

};

#endif // !Level_H

