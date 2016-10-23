#ifndef GameTime_H
#define GameTime_H

#include <ctime>
#include "TimeSpan.h"

namespace freshman
{
	class GameTime
	{

	#pragma region private

	private:

		#pragma region Members

		static TimeSpan tGameTotal;
		static TimeSpan FrameTime;
		static long pre;
		static long cur;

		#pragma endregion

	#pragma endregion

	#pragma region public

	public:

		#pragma region Members

		static long TotalFrames;
			
		#pragma endregion

		#pragma region Methods

		static TimeSpan TGameFrames();
		static TimeSpan TGameTotal();
		static void Update();

		#pragma endregion

	#pragma endregion

	};
}

#endif