#pragma once
#include "Entity.hpp"

class SpriteNode :
    public Entity
{
public:
	enum BackgroundType
	{
		Desert,
		bricks0
	};
public:
	SpriteNode(BackgroundType backgroundtype,Game* game);


private:
	virtual void		drawCurrent() const;
	virtual void		buildCurrent();
private:
	std::string			mBackground;
};
