#pragma once
#include "Entity.hpp"
#include <string>

class AircraftShadow :
	public Entity
{
public:
	enum Type
	{
		EagleShadow,
		RaptorShadow
	};


public:
	AircraftShadow(Type type, Game* game);
	//AircraftShadow();


private:
	virtual void		drawCurrent() const;
	virtual void		buildCurrent();
	//virtual void		GetAirCraftPosition(Aircraft a, AircraftShadow as);


private:
	Type				mType;
	std::string			mSprite;
};
