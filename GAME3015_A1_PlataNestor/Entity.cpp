#include "Entity.hpp"

Entity::Entity(Game* game) : SceneNode(game), mVelocity(0, 0,0)
{
}

void Entity::setVelocity(XMFLOAT3 velocity)
{
	mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy, float vz)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
	mVelocity.z = vz;
}
void Entity::SetXSpeed(float vx)
{
	mVelocity.x = vx;
}

void Entity::SetZSpeed(float vz)
{
	mVelocity.x = vz;
}



XMFLOAT3 Entity::getVelocity() const
{
	return mVelocity;
}

void Entity::updateCurrent(const GameTimer& gt) 
{
	XMFLOAT3 mV;
	mV.x = mVelocity.x * gt.DeltaTime();
	mV.y = mVelocity.y * gt.DeltaTime();
	mV.z = mVelocity.z * gt.DeltaTime();

	move(mV.x, mV.y, mV.z);

	setVelocity(0.0f, 0.0f, 0.0f);// add it

	renderer->World = getWorldTransform();
	renderer->NumFramesDirty++;
}
// add it for input
void Entity::accelerate(XMFLOAT3 velocity)
{
	mVelocity.x = mVelocity.x + velocity.x;
	mVelocity.y = mVelocity.y + velocity.y;
	mVelocity.z = mVelocity.z + velocity.z;
	
}
// add it for input
void Entity::accelerate(float vx, float vy, float vz)
{
	mVelocity.x += vx;
	mVelocity.y += vy;
	mVelocity.z += vz;
}