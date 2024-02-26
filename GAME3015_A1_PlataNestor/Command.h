#pragma once
#include "SceneNode.hpp"

#include <functional>

#include "Category.h"

class SceneNode;

struct Command
{
	Command();

	std::function<void(SceneNode&)>	action;
	unsigned int category;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&)> derivedAction(Function fn)
{
	return [=](SceneNode& node)  //yes you can replace = to fn if you want to be more precise!
    {
			// Check if cast is safe
			assert(dynamic_cast<GameObject*>(&node) != nullptr);

			// Downcast node and invoke function on it
			fn(static_cast<GameObject&>(node));
    };
}
#pragma endregion