#include "GameManager.h"
#include "LevelManager.h"
#include <stdlib.h>

/// <summary>
/// Initializes a new instance of the <see cref="LevelManager" /> class.
/// This class is created by the <see cref="GameManager" /> and contains all level information
/// like characters and the environment.
/// </summary>
LevelManager::LevelManager() : _playerEntity(0), _npcEntity(0), _basicEnemyEntity(0), _groundEntity(0),
playerScript(0), npcScript(0), enemyScript(0), _levelNode(0), _camNode(0)
{
}

/// <summary>
/// Initializes this the level by setting the camera, player, NPC's and surroundings.
/// </summary>
void LevelManager::initialize()
{
	// create level node, the root node for everything in the level
	_levelNode = GameManager::getSingletonPtr()->getSceneManager()->getRootSceneNode()->createChildSceneNode("LevelNode");

	Ogre::SceneNode* playerNode = _levelNode->createChildSceneNode("PlayerNode");
	_camNode = playerNode->createChildSceneNode("CameraNode");

	// set basichub position
	basicHubPosition1 = Ogre::Vector3(750, 0, 750);
	basicHubPosition2 = Ogre::Vector3(-750, 0, -750);


	//player
	_playerEntity = GameManager::getSingletonPtr()->getSceneManager()->createEntity("ninja.mesh");
	playerNode->createChildSceneNode()->attachObject(_playerEntity);
	playerScript = new Player(playerNode, _playerEntity);
	playerScript->initialize();

	
	//spawing NPC objects
	_npcNode = _levelNode->createChildSceneNode("NpcNode");

	for(int i = 0; i < 10;i++)
	{
		Ogre::SceneNode *npc;
		Ogre::Entity *npcEntity = GameManager::getSingletonPtr()->getSceneManager()->createEntity("Number" + Ogre::StringConverter::toString(i),"penguin.mesh");
		npc = _npcNode->createChildSceneNode();
		npc->attachObject(npcEntity);
		npc->setPosition(Ogre::Vector3(Ogre::Math::RangeRandom(-400,400), 0, Ogre::Math::RangeRandom(-400, 400)));
		npc->setOrientation(Ogre::Quaternion(Ogre::Math::RangeRandom(-90, 90), 0, Ogre::Math::RangeRandom(-90, 90),0));
		npcScript = new Npc(_npcNode, npcEntity);
		npcScript->initialize();
	}

    //enemy
	Ogre::SceneNode* enemyNode = _levelNode->createChildSceneNode("EnemyNode");
	_basicEnemyEntity = GameManager::getSingletonPtr()->getSceneManager()->createEntity("robot.mesh");
	enemyNode->createChildSceneNode()->attachObject(_basicEnemyEntity);
	enemyNode->setPosition(Ogre::Vector3(Ogre::Math::RangeRandom(basicHubPosition1.x, 3000), 0, Ogre::Math::RangeRandom(basicHubPosition1.y,3000)));
	enemyScript = new BasicEnemy(enemyNode, _basicEnemyEntity);
	enemyScript->initialize();
	

	// ground 
	createGroundMesh();
	_groundEntity = GameManager::getSingletonPtr()->getSceneManager()->createEntity("ground");
	_levelNode->createChildSceneNode()->attachObject(_groundEntity);
	_groundEntity->setMaterialName("Examples/Rockwall");

	// wall
	createWallMesh();
	_wallEntity = GameManager::getSingletonPtr()->getSceneManager()->createEntity("wall");
	_levelNode->createChildSceneNode()->attachObject(_wallEntity);
	_wallEntity->setMaterialName("Examples/Rockwall");
	

	// camera
	_camNode->attachObject(GameManager::getSingletonPtr()->getCamera());
	_camNode->pitch(Ogre::Degree(10), Ogre::Node::TS_LOCAL);
	startPitchCam = _camNode->getOrientation().getPitch();

	_npcScripts.push_back(npcScript);
	_npcScripts.push_back(enemyScript);

	
	
}

/// <summary>
/// Updates the frame based on the specified fe.
/// </summary>
/// <param name="fe">The frame event.</param>
void LevelManager::update(const Ogre::FrameEvent& pFE)
{
	// update characters
	playerScript->update(pFE.timeSinceLastFrame);

	for(int i = 0; i < _npcScripts.size(); i++)
	{
		_npcScripts[i]->update(pFE.timeSinceLastFrame);
	}
}

/// <summary>
/// Creates the ground mesh.
/// </summary>
void LevelManager::createGroundMesh()
{

	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane(
		"ground",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		1500, 1500, 20, 20,
		true,
		1, 5, 5,
		Ogre::Vector3::UNIT_Z);

	return;
}
/// <summary>
///Create the wall mesh.
/// </summary>
void LevelManager::createWallMesh()
{
	Ogre::Plane wall(Ogre::Vector3::UNIT_X,1000);
	wall.d = 750;
	Ogre::MeshManager::getSingleton().createPlane(
		"wall",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		wall,
		750, 1500, 20, 20,
		true,
		1, 5, 5,
		Ogre::Vector3::UNIT_Z);

	return;

}
/// <summary>
///Check if point is in basichub.
/// </summary>
bool LevelManager::checkIfPositionIsInBasicHub(Ogre::Vector3 *position)
{
	if(basicHubPosition1.x > position->x && position->x < basicHubPosition2.y)
	{
		if (basicHubPosition1.z > position->z && position->z < basicHubPosition2.z)
		{
			return true;

		}
		
	}
	return false;
}


