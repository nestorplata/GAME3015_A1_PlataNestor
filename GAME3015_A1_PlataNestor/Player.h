#pragma once

#include "Command.h"
#include "map"

class CommandQueue;

class Player
{
public:
	Player();
	static const float		PlayerSpeed;
	void                    handleEvent(CommandQueue& commands);
	void					handleRealtimeInput(CommandQueue& commands);
};
#pragma endregion
