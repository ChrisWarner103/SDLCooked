#include <iostream>

#include "SDL.h"
#include "GameManager.h"


using namespace std;
using namespace ChrisFramework;

int main(int arg, char* argv[])
{
	GameManager* game = GameManager::Instance();
	
	srand(time(NULL));

	game->Run();
	
	GameManager::Release();
	game = NULL;

	return 0;
}