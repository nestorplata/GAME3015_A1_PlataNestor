#pragma once
#include "Aircraft.hpp"
#include "Entity.hpp"
#include <string>

class AircraftShadow :
	public Entity
{
public:
	enum Type
	{	
		RaptorShadow
	};


public:
	AircraftShadow(Type type, Game* game);


private:
	virtual void		drawCurrent() const;
	virtual void		buildCurrent();
	virtual void		GetAirCraftPosition(Aircraft a, AircraftShadow as);


private:
	Type				mType;
	std::string			mSprite;
};
