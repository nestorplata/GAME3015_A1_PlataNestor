#pragma once
#include "SceneNode.hpp"
#include "Aircraft.hpp"
#include "AircraftShadow.hpp"
#include "SpriteNode.h"

class World 
{
public:
	explicit							World(Game* window);
	void								update(const GameTimer& gt);
	void								OnPlayerInput(const GameTimer& gt);
	void								draw();

	//void								loadTextures();
	void								buildScene();


private:
	enum Layer
	{
		Background,
		Air,
		LayerCount
	};


private:
	Game*								mGame;

	SceneNode*							mSceneGraph;
	std::array<SceneNode*, LayerCount>	mSceneLayers;

	XMFLOAT4							mWorldBounds;
	XMFLOAT2		    				mSpawnPosition;
	float								mScrollSpeed;
	Aircraft*							mPlayerAircraft;
	SpriteNode*							mBackground;
	Aircraft*							mRaptor1;
	Aircraft*							mRaptor2;

	AircraftShadow*                     mPlayerAircraftShadow;// add 
	int                              Floorloopcounter; // add  to know how many times it's been loop
};
