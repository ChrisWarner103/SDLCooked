#include "PlateContainer.h"
#include "ScreenManager.h"

PlateContainer* PlateContainer::sInstance = NULL;

PlateContainer* PlateContainer::Instance()
{
	if (sInstance == NULL)
		sInstance = new PlateContainer();

	return sInstance;
}

void PlateContainer::Release()
{
	delete sInstance;
	sInstance == NULL;
}

PlateContainer::PlateContainer()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Plate Container Constructed with Param(%p)\n", this);

	mInput = InputManager::Instance();

	plateContainerTexture = new Texture("/Environment/Storage Plate.png");
	collsionArea = new Texture("BoxCollider.png");

	plateContainerTexture->Pos(VEC2_ZERO);

	collsionArea->Parent(plateContainerTexture);
	collsionArea->Pos(Vector2(32.0f, 0.0f));

	collsionArea->Scale(Vector2(0.5f, 1.0f));

	for (int i = 0; i < MAX_AMOUNT_OF_FOOD; i++)
	{
		AddFood();
		plateInContainer++;
	}
}

PlateContainer::~PlateContainer()
{
	for (auto& element : plateContainer)
	{
		delete element;
	}
}

void PlateContainer::AddFood()
{
	Plate* plateImage = new Plate();
	plateImage->Parent(plateContainerTexture);
	plateImage->Active(false);
	plateImage->Pos(VEC2_ZERO);
	this->plateContainer.push_back(plateImage);
}

void PlateContainer::RemoveFood()
{
	plateContainer.at(plateInContainer - 1)->Active(true);
	plateContainer.at(plateInContainer - 1)->itemNumber = (plateInContainer - 1);
	plateInContainer++;

	AddFood();
}

void PlateContainer::RemovePlateFromList(int itemNumber)
{
	plateContainer.erase(plateContainer.begin() + itemNumber);
}

void PlateContainer::Update()
{

	plateContainerTexture->Pos(position(world));

	if (plateContainer.size() < plateInContainer)
	{
		plateInContainer = plateContainer.size();
	}

	if ((ScreenManager::Instance()->returnPlayer()->position().x > (collsionArea->position().x - collsionArea->ScaleDimentions().x)) &&
		(ScreenManager::Instance()->returnPlayer()->position().x < (collsionArea->position().x + collsionArea->ScaleDimentions().x)) &&
		(ScreenManager::Instance()->returnPlayer()->position().y > (collsionArea->position().y - collsionArea->ScaleDimentions().y)) &&
		(ScreenManager::Instance()->returnPlayer()->position().y < (collsionArea->position().y + collsionArea->ScaleDimentions().y)))
	{
		if (mInput->KeyPressed(SDL_SCANCODE_E))
		{
			RemoveFood();
		}
	}

	for (int i = 0; i < plateContainer.size(); i++)
	{
		if (!plateContainer[i]->active())
		{
			plateContainer[i]->Pos(Vector2(plateContainerTexture->position()));
		}

		if (plateContainer[i]->active())
			plateContainer[i]->Update();
	}
}

void PlateContainer::Render()
{
	if (active())
	{
		plateContainerTexture->Render();

		for (int i = 0; i < plateContainer.size(); i++)
		{
			if (plateContainer[i]->active())
				plateContainer[i]->Render();
		}
	}
}
