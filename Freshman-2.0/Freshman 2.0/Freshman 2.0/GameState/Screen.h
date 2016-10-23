#ifndef Screen_H
#define Screen_H

namespace freshman
{
	class Screen
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

		bool Updates;
		bool Draws;

		#pragma endregion
		
		#pragma region Constructor

		Screen()
		{
			Updates = true;
			Draws = true;

			//Initialize();
		}

		#pragma endregion

		#pragma region Operator

		#pragma endregion

		#pragma region Methods

		virtual void Initialize() = 0;
		virtual void LoadContent() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;

		#pragma endregion

	#pragma endregion

	};
}

#endif