#pragma once
#include "Entity.hpp"

class DebugShadowMap :
    public Entity
{
public:
	DebugShadowMap(Game* game);

private:
	virtual void		drawCurrent() const;
	virtual void		buildCurrent();
};
