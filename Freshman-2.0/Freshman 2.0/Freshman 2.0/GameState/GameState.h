#ifndef GameState_H
#define GameState_H

#include <Utilities\GameTime.h>

#include <Windows.h>

#include <vector>

#include <GameState\Screen.h>
#include <Screens\Screen1.h>

namespace freshman
{
	class Screen;
	class GameState
	{

	#pragma region private

	private:

		#pragma region Members

		static std::vector<Screen*> ToUpdate;
		static std::vector<Screen*> Screens;

		static float MoniterRefreshRate;

		#pragma endregion

	#pragma endregion

	#pragma region public

	public:

		#pragma region Members

		static float PreferredTimeStep;
		static bool VSync;

		#pragma endregion

		#pragma region Methods

	    static void RemoveScreen(Screen*);
		static void AddScreen(Screen*);
		static void Play(); 

		#pragma endregion

	#pragma endregion

	};

}

#endif

