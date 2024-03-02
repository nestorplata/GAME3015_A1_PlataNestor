
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
#include <fstream>
const float Player::PlayerSpeed = 5.0f; //0.05f;

std::ofstream myfile;


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


void Player::handleEvent(CommandQueue& commands)
{
	if (GetAsyncKeyState('P') & 0x8000)
	{
		

		Command output;
		output.category = Category::PlayerAircraft;
		output.action = [](SceneNode& s, const float dt) {
			std::string ms;
			ms = std::to_string(dt);

			

			myfile.open("example.txt");
			myfile << " OurAirPlane_X: " << s.getWorldPositionX() << "\n";
			myfile << " OurAirPlane_Y: " << s.getWorldPositionY() << "\n";
			myfile << " OurAirPlane_Z: " << s.getWorldPositionZ() << "\n";
			myfile << " Timerdelta: " << ms << "\n";



			myfile.close();

			};
		commands.push(output);
	}
}
#pragma endregion