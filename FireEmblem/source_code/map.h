#pragma once

//============================================================================
//=																			 =
//=									 Map									 =
//=																			 =
//============================================================================

#ifndef MAP_H_
#define MAP_H_

class CMap
{
public:
	CMap();
	~CMap();

	void Update();
	void Draw();

private:
	std::unique_ptr<CLoadMap> mpLoadMap;

	std::unique_ptr<CAllies> mpAllies;
	std::unique_ptr<CEnemy> mpEnemy;
	std::unique_ptr<CPlain> mpPlain;
	std::unique_ptr<CMountain> mpMountain;
	std::unique_ptr<CForest> mpForest;

	CObjectType** mObjectType;
	int mMapX = 0;
	int mMapZ = 0;
};

#endif // !MAP_H_
