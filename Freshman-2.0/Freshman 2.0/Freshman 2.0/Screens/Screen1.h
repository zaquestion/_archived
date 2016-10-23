#ifndef State1_H
#define State1_H

#include <GameState\Screen.h>

#include <iostream>

namespace freshman
{
	class Screen1 : public Screen
	{

	#pragma region private

	private:

		#pragma region Members

		#pragma endregion

		#pragma region Methods

		#pragma endregion

	#pragma endregion

	#pragma region public

	public:

		#pragma region Members

		#pragma endregion

		#pragma region Constructor

		Screen1()
			: Screen()
		{
			Initialize();
		}
		
		#pragma endregion

		#pragma region Methods

		virtual void Initialize();
		virtual void LoadContent();
		virtual void Update();
		virtual void Draw();

		#pragma endregion

	#pragma endregion

	};
}

#endif