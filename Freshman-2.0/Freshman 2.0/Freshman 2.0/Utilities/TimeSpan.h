#ifndef TimeSpan_H
#define TimeSpan_H

#include <ctime>

namespace freshman
{
	class TimeSpan
	{

	#pragma region private

	private:

		#pragma region Members

		long Value;

		#pragma endregion

	#pragma endregion

	#pragma region public

	public:

		#pragma region Operators

		TimeSpan operator+(TimeSpan &T) { return TimeSpan(this->Ticks() + T.Ticks()); }
		friend TimeSpan operator-(TimeSpan &T1, TimeSpan &T2) { return TimeSpan(T1.Ticks() - T2.Ticks()); }

		#pragma endregion
		
		#pragma region Constructor

		TimeSpan(long);

		#pragma endregion

		#pragma region Methods

		void Remove();
		long Ticks();
		float Seconds();
		float mSeconds();
		float Minutes();
		float Hours();
		

		#pragma endregion

	#pragma endregion

	};
}

#endif