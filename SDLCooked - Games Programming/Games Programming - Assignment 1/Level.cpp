#include "Level.h"
#include "GameManager.h"

Level::Level(Player* player)
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Level Constructed with Param(%p)\n", this);

	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mRecipeDecider = RecipeDecider::Instance();

	//Building the level

	levelFloor = new Texture("Environment/LevelFloor.png");

	counter1 = new Texture("Environment/Counter.png"); // 8 long
	counter2 = new Texture("Environment/Counter.png"); // 2 long
	counter3 = new Texture("Environment/Counter.png"); // 12 long
	counter4 = new Texture("Environment/Counter.png"); // 2 long
	counter5 = new Texture("Environment/Counter.png"); // 3 long

	//Containers

	plateCrate = PlateContainer::Instance();
	meatCrate = new ContainerMeat();
	cheeseCrate = new FoodContainerCheese();
	lettuceCrate = new FoodContainerLettuce();
	bunCrate = FoodContainerBuns::Instance();

	cooker1 = new Cooker();
	cooker2 = new Cooker();
	cooker3 = new Cooker();
	cooker4 = new Cooker();
	cooker5 = new Cooker();

	choppingStation1 = new Chopping();
	choppingStation2 = new Chopping();
	choppingStation3 = new Chopping();
	choppingStation4 = new Chopping();

	resturantOutgoing = new Goal();

	levelFloor->Pos(Vector2((Graphics::Instance()->SCREEN_WIDTH * 0.5f), (Graphics::Instance()->SCREEN_HEIGHT * 0.5f)));

	counter1->Scale(Vector2(9.0f, 1.0f));
	counter2->Scale(Vector2(1.0f, 2.0f));
	counter3->Scale(Vector2(12.0f, 1.0f));
	counter4->Scale(Vector2(1.0f, 3.0f));
	counter5->Scale(Vector2(1.0f, 3.0f));

	counter1->Pos(Vector2(480.0f, 172.0f));
	counter2->Pos(Vector2(224.0f, 588.0f));
	counter3->Pos(Vector2(640.0f, 620.0f));
	counter4->Pos(Vector2(1064.0f, 556.0f));
	counter5->Pos(Vector2(1065.0f, 236.0f));

	plateCrate->Pos(Vector2(224.0f, 236.0f));
	meatCrate->Pos(Vector2(224.0f, 300.0f));
	cheeseCrate->Pos(Vector2(224.0f, 364.0f));
	lettuceCrate->Pos(Vector2(224.0f, 428.0f));
	bunCrate->Pos(Vector2(224.0f, 492.0f));

	cooker1->Pos(Vector2(1001.0f, 172.0f));
	cooker2->Pos(Vector2(937.0f, 172.0f));
	cooker3->Pos(Vector2(873.0f, 172.0f));
	cooker4->Pos(Vector2(809.0f, 172.0f));
	cooker5->Pos(Vector2(745.0f, 172.0f));

	choppingStation1->Pos(Vector2(1001.0f, 620.0f));
	choppingStation2->Pos(Vector2(937.0f, 620.0f));
	choppingStation3->Pos(Vector2(873.0f, 620.0f));
	choppingStation4->Pos(Vector2(809.0f, 620.0f));


	resturantOutgoing->Rotation(90.0f);

	resturantOutgoing->Pos(Vector2(1065.0f, 396.0f));

	//Building the UI
	playerScore = new Scoreboard(244, 244, 244);
	scoreCoin = new Texture("Coin.png");
	stopWatch = new Texture("Stopwatch.png");
	countDownTimer = new Scoreboard(160, 28, 32);

	scoreCoin->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.1f, Graphics::Instance()->SCREEN_HEIGHT * 0.85f));
	playerScore->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.1f, Graphics::Instance()->SCREEN_HEIGHT * 0.85f));

	stopWatch->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.9f, Graphics::Instance()->SCREEN_HEIGHT * 0.85f));
	countDownTimer->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.92f, Graphics::Instance()->SCREEN_HEIGHT * 0.85f));

	scoreCoin->Scale(Vector2(0.4f, 0.4f));
	stopWatch->Scale(Vector2(0.4f, 0.4f));

	AssignPlayer(player);
	RecipeDecider::CurrentPlayer(player);

	endLevelScreen = new Texture("Level Complete Screen.png");
	endLevelScreen->Active(false);
	endLevelScreen->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH *0.5, Graphics::Instance()->SCREEN_HEIGHT * 0.5));

	exitButton = new Texture("Exit Button.png");
	exitButton->Parent(endLevelScreen);
}

Level::~Level()
{
	//Release Environment

	delete levelFloor;
	delete counter1;
	delete counter2;
	delete counter3;
	delete counter4;
	delete counter5;
	delete bunCrate;
	delete meatCrate;
	delete cheeseCrate;
	delete lettuceCrate;
	delete plateCrate;
	delete cooker1;
	delete cooker2;
	delete cooker3;
	delete cooker4;
	delete cooker5;
	delete choppingStation1;
	delete choppingStation2;
	delete choppingStation3;
	delete choppingStation4;
	delete resturantOutgoing;
	delete endLevelScreen;

	levelFloor = NULL;
	 counter1 = NULL;
	 counter2 = NULL;
	 counter3 = NULL;
	 counter4 = NULL;
	 counter5 = NULL;
	 bunCrate = NULL;
	 meatCrate = NULL;
	 cheeseCrate = NULL;
	 lettuceCrate = NULL;
	 plateCrate = NULL;
	 cooker1 = NULL;
	 cooker2 = NULL;
	 cooker3 = NULL;
	 cooker4 = NULL;
	 cooker5 = NULL;
	 choppingStation1 = NULL;
	 choppingStation2 = NULL;
	 choppingStation3 = NULL;
	 choppingStation4 = NULL;
	 resturantOutgoing = NULL;
	 endLevelScreen = NULL;

	//Release UI

	delete playerScore;
	delete scoreCoin;
	delete stopWatch;
	delete countDownTimer;

	playerScore = NULL;
	scoreCoin = NULL;
	stopWatch = NULL;
	countDownTimer = NULL;
}

void Level::SetPlayerScore(int score)
{
	playerTotalScore += score;
	playerScore->SetScore(playerTotalScore);
}

void Level::Update()
{
	switch (currentLevelState)
	{
	case LEVELSTATES::playing:
		resturantOutgoing->Update();

		cooker1->Update();
		cooker2->Update();
		cooker3->Update();
		cooker4->Update();
		cooker5->Update();

		choppingStation1->Update();
		choppingStation2->Update();
		choppingStation3->Update();
		choppingStation4->Update();

		plateCrate->Update();
		meatCrate->Update();
		cheeseCrate->Update();
		lettuceCrate->Update();
		bunCrate->Update();

		playerScore->SetScore(mPlayer->Score());

		UpdateTimer();

		if (timer <= 0)
		{
			currentLevelState = LEVELSTATES::finished;
		}

		if(mInput->KeyPressed(SDL_SCANCODE_0))
			currentLevelState = LEVELSTATES::finished;
		break;

	case LEVELSTATES::finished:
		
		playerScore->Pos(Vector2(800.0f, 450.0f));
		endLevelScreen->Active(true);
		ScreenManager::Instance()->currentScreen = ScreenManager::SCREENS::end;

		exitButton->Pos(Vector2(400.0f, 250.0f));

		InputManager::Instance()->Update();
		int mouseX = InputManager::Instance()->MousePosition().x;
		int mouseY = InputManager::Instance()->MousePosition().y;

		float scaleX = ((float)Graphics::Instance()->width / Graphics::SCREEN_WIDTH);
		float scaleY = ((float)Graphics::Instance()->height / Graphics::SCREEN_HEIGHT);

		mouseX /= scaleX;
		mouseY /= scaleY;

		if ((mouseX > (exitButton->position(GameEntity::world).x - (174.0f / 2))) && (mouseX < (exitButton->position(GameEntity::world).x + (174.0f / 2)))
			&& (mouseY > (exitButton->position(GameEntity::world).y - (91.0f / 2))) && (mouseY < (exitButton->position(GameEntity::world).y + (91.0f / 2))))
		{
			exitButton->Scale(Vector2(0.55f, 0.55f));

			if (InputManager::Instance()->MouseButtonDown(InputManager::left))
			{
				exitButton->Scale(Vector2(0.45f, 0.45f));
			}
			else if (InputManager::Instance()->MouseButtonReleased(InputManager::left))
			{
				GameManager::Instance()->QuitGame();
			}
		}
		else
		{
			exitButton->Scale(Vector2(0.5f, 0.5f));
		}

		break;
	}

}

void Level::UpdateTimer()
{
	timer -= mTimer->DeltaTime();

	countDownTimer->SetScore((int)timer);
}

void Level::AssignPlayer(Player* player)
{
	mPlayer = player;
}

void Level::Render()
{
	switch (currentLevelState)
	{
	case LEVELSTATES::playing:
		levelFloor->Render();

		resturantOutgoing->Render();

		counter1->Render();
		counter2->Render();
		counter3->Render();
		counter4->Render();
		counter5->Render();

		cooker1->Render();
		cooker2->Render();
		cooker3->Render();
		cooker4->Render();
		cooker5->Render();

		choppingStation1->Render();
		choppingStation2->Render();
		choppingStation3->Render();
		choppingStation4->Render();

		//These always need to be rendered last due to they render the food as well.

		plateCrate->Render();
		bunCrate->Render();
		meatCrate->Render();
		lettuceCrate->Render();
		cheeseCrate->Render();


		//UI needs to render last as it needs to be above everything
		stopWatch->Render();
		countDownTimer->Render();
		scoreCoin->Render();
		playerScore->Render();
		break;

	case LEVELSTATES::finished:

		if (endLevelScreen->active())
		{

			endLevelScreen->Render();
			playerScore->Render();
			exitButton->Render();
		}

		break;
	}


}

