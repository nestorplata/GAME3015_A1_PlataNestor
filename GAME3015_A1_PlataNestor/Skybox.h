#pragma once
#include "Entity.hpp"

class Skybox :
    public Entity
{
public:
	Skybox(Game* game);

private:
	virtual void		drawCurrent() const;
	virtual void		buildCurrent();
};
