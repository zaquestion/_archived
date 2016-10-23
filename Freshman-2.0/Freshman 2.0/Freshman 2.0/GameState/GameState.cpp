#include "GameState.h"


using namespace std;

#pragma region TypeDef

typedef unsigned int uint;

#pragma endregion

namespace freshman
{
	vector<Screen*> GameState::Screens;
	vector<Screen*> GameState::ToUpdate;

	#pragma region Play

	void GameState::Play()
	{
		
	}

	#pragma endregion

	#pragma region Methods

	#pragma region AddScreen

	void GameState::AddScreen(Screen *screen)
	{
		Screens.push_back(screen);
	}

	#pragma endregion

	#pragma region RemoveScreen

	void GameState::RemoveScreen(Screen *screen)
	{ 
		//only until I know better.
		uint deleteAt;
		for(uint i = 0; i < Screens.size(); i++) { if (Screens[i] == screen) deleteAt = i; }
		Screens.erase(Screens.begin() + deleteAt);
		delete screen;
	}

	#pragma endregion

	#pragma endregion

}

void main()
{
	freshman::GameState::AddScreen(new freshman::Screen1());

	freshman::GameState::Play();
};