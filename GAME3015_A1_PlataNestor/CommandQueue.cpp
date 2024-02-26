
#pragma region
/// add it for input
///
#include "CommandQueue.h"
#include "SceneNode.hpp""
void CommandQueue::push(const Command& command)
{
	mQueue.push(command);
}

Command CommandQueue::pop()
{
	Command command = mQueue.front();
	mQueue.pop();
	return command;
}

bool CommandQueue::isEmpty() const
{
	return mQueue.empty();
}
#pragma endregion