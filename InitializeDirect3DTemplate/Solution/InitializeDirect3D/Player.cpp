
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

const float Player::PlayerSpeed = 30.0f;//3.0f; //0.05f;

std::ofstream myfile;
Input::Keys myKeys;

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
	// Set initial key bindings
	mKeyBinding[Input::A] = MoveLeft;
	mKeyBinding[Input::D] = MoveRight;
	mKeyBinding[Input::W] = MoveUp;
	mKeyBinding[Input::S] = MoveDown;
	mKeyBinding[Input::P] = GetPosition;
	//myKeys = Input::P;
	// Set initial action bindings
	initializeActions();

	// Assign all categories to player's aircraft
	for (auto& pair : mActionBinding)
		pair.second.category = Category::PlayerAircraft;

}



//void Player::handleRealtimeInput(CommandQueue& commands)
//{
//	if (GetAsyncKeyState(Input::D) & 0x8000  )
//	{
//		
//			Command moveLeft;
//			moveLeft.category = Category::PlayerAircraft;
//			moveLeft.action = derivedAction<Aircraft>(
//				AircraftMover(PlayerSpeed, 0.f, 0.f)
//			);
//			commands.push(moveLeft);
//		
//	}
//	
//
//	if (GetAsyncKeyState(Input::A) & 0x8000 )
//	{
//
//		Command moveRight;
//		moveRight.category = Category::PlayerAircraft;
//		moveRight.action = derivedAction<Aircraft>(
//			AircraftMover(-PlayerSpeed , 0.f, 0.f)
//		);
//		commands.push(moveRight);
//
//
//	}
//	
//
//	if (GetAsyncKeyState(Input::W) & 0x8000  )
//	{
//
//		Command moveUp;
//		moveUp.category = Category::PlayerAircraft;
//		moveUp.action = derivedAction<Aircraft>(
//			AircraftMover(0.f, 0.f, PlayerSpeed )
//		);
//		commands.push(moveUp);
//
//	}
//	
//
//	if (GetAsyncKeyState(Input::S) & 0x8000 )
//	{
//
//		Command moveDown;
//		moveDown.category = Category::PlayerAircraft;
//		moveDown.action = derivedAction<Aircraft>(
//			AircraftMover(0.f, 0.f, -PlayerSpeed )
//		);
//		commands.push(moveDown);
//
//	}
//	
//	
//
//}

void Player::handleRealtimeInput(CommandQueue& commands)
{
	 //Traverse all assigned keys and check if they are pressed
	for (auto pair : mKeyBinding)
	{
		 //If key is pressed, lookup action and trigger corresponding command
		if (/*(GetAsyncKeyState(pair.first)*/  GetKeyState(pair.first) < 0 && isRealtimeAction(pair.second))
			commands.push(mActionBinding[pair.second]);
	}
}
//void Player::handleRealtimeInput(CommandQueue& commands, WPARAM btnState)
//{
//	Input::Keys tempKeys;
//
//	tempKeys = (Input::Keys)btnState;
//
//	 Traverse all assigned keys and check if they are pressed
//	for (auto pair : mKeyBinding)
//	{
//		 If key is pressed, lookup action and trigger corresponding command
//		if (tempKeys == pair.first && isRealtimeAction(pair.second))
//			commands.push(mActionBinding[pair.second]);
//	}
//}

//void Player::handleEvent(CommandQueue& commands)
//{
//	if (GetAsyncKeyState('P') & 0x8000)
//	{
//		
//
//		Command output;
//		output.category = Category::PlayerAircraft;
//		output.action = [](SceneNode& s, const float dt) {
//			std::string ms;
//			ms = std::to_string(dt);
//
//			
//
//			myfile.open("example.txt");
//			myfile << " OurAirPlane_X: " << s.getWorldPositionX() << "\n";
//			myfile << " OurAirPlane_Y: " << s.getWorldPositionY() << "\n";
//			myfile << " OurAirPlane_Z: " << s.getWorldPositionZ() << "\n";
//			myfile << " Timerdelta: " << ms << "\n";
//
//
//
//			myfile.close();
//
//			};
//		commands.push(output);
//	}
//
//
//
//}


void Player::initializeActions()
{
	

	mActionBinding[MoveLeft].action = derivedAction<Aircraft>(AircraftMover(-PlayerSpeed , 0.f, 0.f));
	mActionBinding[MoveRight].action = derivedAction<Aircraft>(AircraftMover(PlayerSpeed, 0.f, 0.f));
	mActionBinding[MoveUp].action = derivedAction<Aircraft>(AircraftMover(0.f, 0.f, PlayerSpeed));
	mActionBinding[MoveDown].action = derivedAction<Aircraft>(AircraftMover(0.f, 0.f, -PlayerSpeed));
	mActionBinding[GetPosition].action = [](SceneNode& s, const float dt) {
		std::string ms;
		ms = std::to_string(dt);



		myfile.open("OurAirplane.txt", std::ios::app);
		myfile << "\n";
		myfile << " OurAirPlane_X: " << s.getWorldPositionX() << "\n";
		myfile << " OurAirPlane_Y: " << s.getWorldPositionY() << "\n";
		myfile << " OurAirPlane_Z: " << s.getWorldPositionZ() << "\n";
		myfile << " Timerdelta: " << ms << "\n";



		myfile.close();

		};
	// cout version that doesnt work
		/*{
			std::string ms;
		ms = std::to_string(dt);
		
		std::cout << " OurAirPlane_X: " << s.getWorldPositionX() << "\n";
		std::cout << " OurAirPlane_Y: " << s.getWorldPositionY() << "\n";
		std::cout << " OurAirPlane_Z: " << s.getWorldPositionZ() << "\n";
		std::cout << " Timerdelta: " << ms << "\n";

		};*/
}

//void Player::handleEvent(CommandQueue& commands)
//{
//	// Check if pressed key appears in key binding, trigger command if so
//	if (GetAsyncKeyState( myKeys))
//	{
//		// Check if pressed key appears in key binding, trigger command if so
//		auto found = mKeyBinding.find( myKeys);
//		if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
//			commands.push(mActionBinding[found->second]);
//	}
//	
//}
	
//void Player::handleEvent(CommandQueue& commands)
//{
//	// Traverse all assigned keys and check if they are pressed
//	for (auto pair : mKeyBinding)
//	{
//		// If key is pressed, lookup action and trigger corresponding command
//		if (GetAsyncKeyState(pair.first) && !isRealtimeAction(pair.second)&& isEventAction(pair.second))
//			commands.push(mActionBinding[pair.second]);
//	}
//}
void Player::handleEvent(CommandQueue& commands, WPARAM btnState)
{
	Input::Keys tempKeys;

	 tempKeys = (Input::Keys)btnState;

	auto found = mKeyBinding.find(tempKeys);
	if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
		commands.push(mActionBinding[found->second]);

}


bool Player::isRealtimeAction(Action action)
{
	switch (action)
	{
	case MoveLeft:
	case MoveRight:
	case MoveDown:
	case MoveUp:
		return true;

	default:
		return false;
	}
}
//bool Player::isEventAction(Action action)
//{
//	switch (action)
//	{
//	case  GetPosition:
//		return true;
//
//	default:
//		return false;
//	}
//}

void Player::assignKey(Action action, Input::Keys key)
{
	// Remove all keys that already map to action
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
	{
		if (itr->second == action)
			mKeyBinding.erase(itr++);
		else
			++itr;
	}

	// Insert new binding
	mKeyBinding[key] = action;
}

Input::Keys Player::getAssignedKey(Action action) const
{
	for (auto pair : mKeyBinding)
	{
		if (pair.second == action)
			return pair.first;
	}

	return Input::Keys::Unknown;
}


#pragma endregion