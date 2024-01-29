#include "World.hpp"
#include <string>//
#include <iostream>// to print to console

World::World(Game* game)
	: mSceneGraph(new SceneNode(game))
	, mGame(game)
	, mPlayerAircraft(nullptr)
	, mBackground(nullptr)
	, mWorldBounds(-1.5f, 1.5f, 200.0f, 0.0f) //Left, Right, Down, Up
	, mSpawnPosition(0.f, 0.f)
	, mScrollSpeed(-1.0f)
	, Floorloopcounter(0)
{
}

void World::update(const GameTimer& gt)
{
	// loop background
	if (mBackground->getWorldPosition().z < -10.0f )
	{
		// place back  the mBackground to it's original position
		mBackground->setPosition(0, 0, 0);		

		// tracking how many times it loop.
		Floorloopcounter = Floorloopcounter +1;
		//std::cout << "Floorloopcounter: "<< Floorloopcounter;
		
	}
	else
	{
		// to move the background
		mBackground->setVelocity(0, 0, mScrollSpeed + gt.DeltaTime());
	}

	
	/*float playerWPX = mPlayerAircraft->getWorldPositionX();
	float playerWPY = mPlayerAircraft->getWorldPositionY();
	float PlayerWPZ = mPlayerAircraft->getWorldPositionY();*/
	

	

	OnPlayerInput(gt);

	mSceneGraph->update(gt);
}

void World::OnPlayerInput(const GameTimer& gt)
{
	const float dt = gt.DeltaTime();
	float x = 0;
	float z = 0;
	float Speed = 500.0f;

	if (GetAsyncKeyState('A') & 0x8000)
	{
		if (mPlayerAircraft->getWorldPositionX() >= -1.0)
		{
			x -= Speed;
		}
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		if (mPlayerAircraft->getWorldPositionZ() >= -0.9)
		{
			z -= Speed;
		}
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		if (mPlayerAircraft->getWorldPositionX() <= 1.0)
		{
			x += Speed;
		}
	}
	if (GetAsyncKeyState('W') & 0x8000)
	{
		//
		if (mPlayerAircraft->getWorldPositionZ() <= 0.9)
		{
			z += Speed;
		}
		/*float PlayerWPZ = mPlayerAircraft->getWorldPositionZ();
		float playerWPX = mPlayerAircraft->getWorldPositionX();
		float playerWPY = mPlayerAircraft->getWorldPositionY();*/
	}

	if (abs(x) == abs(z) &&x!=0)
	{
		x *= 0.7071;
		z *= 0.7071;
	}
	mPlayerAircraft->setVelocity(x * dt, 0, z * dt);
	mPlayerAircraftShadow->setVelocity(x * dt, 0, z * dt);
}

void World::draw()
{
	mSceneGraph->draw();
}

void World::buildScene()
{
	std::unique_ptr<Aircraft> player(new Aircraft(Aircraft::Eagle, mGame));
	mPlayerAircraft = player.get();
	mPlayerAircraft->setPosition(0, 0.1, 0.0);
	mPlayerAircraft->setScale(0.5, 0.5, 0.5);
	//mPlayerAircraft->setVelocity(mScrollSpeed, 0.0, 0.0);
	mSceneGraph->attachChild(std::move(player));

	std::unique_ptr<Aircraft> enemy1(new Aircraft(Aircraft::Raptor, mGame));
	auto raptor = enemy1.get();
	raptor->setPosition(0.5, 0.1, 1);
	raptor->setScale(1.0, 1.0, 1.0);
	raptor->setWorldRotation(0, XM_PI, 0);
	mPlayerAircraft->attachChild(std::move(enemy1));

	std::unique_ptr<Aircraft> enemy2(new Aircraft(Aircraft::Raptor, mGame));
	auto raptor2 = enemy2.get();
	raptor2->setPosition(-0.5, 0.1, 1);
	raptor2->setScale(1.0, 1.0, 1.0);
	raptor2->setWorldRotation(0, XM_PI, 0);
	mPlayerAircraft->attachChild(std::move(enemy2));



	std::unique_ptr<AircraftShadow> raptorshadowtest(new AircraftShadow(AircraftShadow::RaptorShadow, mGame));
	auto raptorshadow = raptorshadowtest.get();
	raptorshadow->setPosition(0.6, 0.0, 1);
	raptorshadow->setScale(0.5, 0.5, 1.0);
	raptorshadow->setWorldRotation(0, XM_PI, 0);
	mPlayerAircraft->attachChild(std::move(raptorshadowtest));
	

	

	std::unique_ptr<AircraftShadow> raptorshadowtest2(new AircraftShadow(AircraftShadow::RaptorShadow, mGame));
	auto raptorshadow2 = raptorshadowtest2.get();
	raptorshadow2->setPosition(-0.6, 0.0, 1);
	raptorshadow2->setScale(0.5, 0.5, 1.0);
	raptorshadow2->setWorldRotation(0, XM_PI, 0);
	mPlayerAircraft->attachChild(std::move(raptorshadowtest2));



	std::unique_ptr<AircraftShadow> Eagleshadowtest1(new AircraftShadow(AircraftShadow::EagleShadow, mGame));
	mPlayerAircraftShadow = Eagleshadowtest1.get();
	mPlayerAircraftShadow->setPosition(0.0, -0.01, -0.5);
	mPlayerAircraftShadow->setScale(0.5, 0.5, 0.5);
	mPlayerAircraftShadow->setWorldRotation(0, 0, 0);
	//mPlayerAircraft->attachChild(std::move(Eagleshadowtest1));
	mPlayerAircraft->attachChild(std::move(Eagleshadowtest1));
	

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mGame));
	mBackground = backgroundSprite.get();
	//mBackground->setPosition(mWorldBounds.left, mWorldBounds.top);
	mBackground->setPosition(0, 0, 0.0);
	mBackground->setScale(50.0, 50.0, 100.0);
	//mBackground->setVelocity(0, 0, -mScrollSpeed);
	mSceneGraph->attachChild(std::move(backgroundSprite));

	mSceneGraph->build();
}
