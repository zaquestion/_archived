#include "GameTime.h"

#pragma region TypeDef

typedef unsigned int uint;

#pragma endregion

namespace freshman
{
	#pragma region Members

	long GameTime::pre = 0;
	long GameTime::cur = 0;
	long GameTime::TotalFrames = 0;
	TimeSpan GameTime::tGameTotal = TimeSpan(0);
	TimeSpan GameTime::FrameTime = TimeSpan(0);

	#pragma endregion

	#pragma region Methods

	#pragma region Update

	void GameTime::Update()
	{
		pre = cur;
		cur = std::clock();
		FrameTime = cur - pre > 50000 ? 50000 : cur - pre;
		tGameTotal = tGameTotal + FrameTime;
		TotalFrames++;
	}

	#pragma endregion

	#pragma region Real Game Frames

	TimeSpan GameTime::TGameFrames()
	{
		return FrameTime;
	}

	#pragma endregion

	#pragma region  Game Time Total

	TimeSpan GameTime::TGameTotal()
	{
		return tGameTotal;
	}

	#pragma endregion

	#pragma endregion
}
