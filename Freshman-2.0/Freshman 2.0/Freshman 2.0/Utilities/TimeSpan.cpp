#include "TimeSpan.h"

#pragma region TypeDef

typedef unsigned int uint;

#pragma endregion

namespace freshman
{
	#pragma region Constructor

	TimeSpan::TimeSpan(long Ticks)
		: Value(Ticks)
	{
	}

	#pragma endregion

	#pragma region Methods

	#pragma region Remove	

	void TimeSpan::Remove()
	{
		delete this;
	}

	#pragma endregion

	#pragma region Ticks

	long TimeSpan::Ticks()
	{
		return Value;
	}

	#pragma endregion

	#pragma region miliSeconds

	float TimeSpan::mSeconds()
	{
		return (float)Value / 100.0f;
		
	}

	#pragma endregion

	#pragma region Seconds

	float TimeSpan::Seconds()
	{
		return (float)Value / 1000.0f;
	}

	#pragma endregion

	#pragma region Minutes

	float TimeSpan::Minutes()
	{
		return (float)Value / 6000.0f;
	}

	#pragma endregion

	#pragma region Hours

	float TimeSpan::Hours()
	{
		return (float)Value / 36000.0f;
	}

	#pragma endregion

	#pragma endregion
}
