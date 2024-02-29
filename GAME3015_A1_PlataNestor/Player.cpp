
#include "Player.h"
#include "SceneNode.hpp"

#pragma region step 18
#include "Player.h"
#include "CommandQueue.h"
#include "Aircraft.hpp"

#include "map"
#include "string"
#include "algorithm"
#include "iostream"
const float Player::PlayerSpeed = 1.0f; //0.05f;

struct AircraftMover
{
	AircraftMover(float vx, float vy, float vz)
		: velocity(vx, vy, vz)
	{
	}

	void operator() (SceneNode& node, const float dt) const
	{
		Aircraft& aircraft = static_cast<Aircraft&>(node);
		aircraft.accelerate(velocity);
		
	}

	XMFLOAT3 velocity;
};

Player::Player()
{

}



void Player::handleRealtimeInput(CommandQueue& commands)
{
	if (GetAsyncKeyState('D') & 0x8000  )
	{
		
			Command moveLeft;
			moveLeft.category = Category::PlayerAircraft;
			moveLeft.action = derivedAction<Aircraft>(
				AircraftMover(PlayerSpeed, 0.f, 0.f)
			);
			commands.push(moveLeft);
		
	}
	

	if (GetAsyncKeyState('A') & 0x8000 )
	{

		Command moveRight;
		moveRight.category = Category::PlayerAircraft;
		moveRight.action = derivedAction<Aircraft>(
			AircraftMover(-PlayerSpeed , 0.f, 0.f)
		);
		commands.push(moveRight);


	}
	

	if (GetAsyncKeyState('W') & 0x8000  )
	{

		Command moveUp;
		moveUp.category = Category::PlayerAircraft;
		moveUp.action = derivedAction<Aircraft>(
			AircraftMover(0.f, 0.f, PlayerSpeed )
		);
		commands.push(moveUp);

	}
	

	if (GetAsyncKeyState('S') & 0x8000 )
	{

		Command moveDown;
		moveDown.category = Category::PlayerAircraft;
		moveDown.action = derivedAction<Aircraft>(
			AircraftMover(0.f, 0.f, -PlayerSpeed )
		);
		commands.push(moveDown);

	}
	


}
#pragma endregion