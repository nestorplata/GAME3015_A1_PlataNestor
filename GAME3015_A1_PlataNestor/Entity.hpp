#pragma once
#include "SceneNode.hpp"

class Entity :
    public SceneNode
{
public:
	Entity(Game* game);
	void				setVelocity(XMFLOAT3 velocity);
	void				setVelocity(float vx, float vy, float vz);
	void				SetXSpeed(float vx);
	void				SetZSpeed(float vz);
	void				setLife(float hp);
	void				FireMissile();
	XMFLOAT3			getVelocity() const;
	void				getLife();
	void				accelerate(XMFLOAT3 velocity);// add it for input
	void				accelerate(float vx, float vy, float vz);// add it for input

	virtual	void		updateCurrent(const GameTimer& gt);

public:
	XMFLOAT3		mVelocity;
	float			life;
	bool			isFriendly;
	bool			isMissileFired;
};

