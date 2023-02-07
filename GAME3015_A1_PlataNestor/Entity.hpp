#pragma once
#include "SceneNode.hpp"

class Entity :
    public SceneNode
{
public:
	Entity(Game* game);
	void				setVelocity(XMFLOAT2 velocity);
	void				setVelocity(float vx, float vy);
	void				setLife(float hp);
	void				FireMissile();
	XMFLOAT2			getVelocity() const;
	void				getLife();


	virtual	void		updateCurrent(const GameTimer& gt);

public:
	XMFLOAT2		mVelocity;
	float			life;
	bool			isFriendly;
	bool			isMissileFired;
};

