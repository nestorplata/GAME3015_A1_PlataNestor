#pragma once
#include "SceneNode.hpp"
#include <fstream>
#include "Aircraft.hpp"
#include "AircraftShadow.hpp"
#include "SpriteNode.h"
#include "CommandQueue.h"// add it for input
#include "Command.h"// add it for input

class World 
{
public:
	explicit							World(Game* window);
	void								update(const GameTimer& gt);
	void								OnPlayerInput(const GameTimer& gt);
	void								MoveRaptorSideToSide(const GameTimer& gt);
	void								draw();

	//void								loadTextures();
	void								buildScene();
	CommandQueue&                       getCommandQueue(); /// add it for input

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
	bool                             IsRaptorOneLimitX, IsRaptorTwoLimitX; // use control the enemie planes
	float                            Raptor1_X , Raptor2_X;// used store the x value ememy air planes
	std::ofstream                         myfile; // used as text console / debug
	CommandQueue						    mCommandQueue;// add it for input

};
