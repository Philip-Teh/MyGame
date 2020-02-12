#pragma once

//============================================================================
//=																			 =
//=							クラス　ロードマップ							 =
//=																			 =
//============================================================================

#ifndef LOADMAP_H_
#define LOADMAP_H_

class CLoadMap
{
public:
	void Load(int mapID);

	void ReleaseMap(void);
	
	CObjectType** GetType() { return mpType; }
	CBoxType** GetBox() { return mpBox; }
	//std::list<XMINT2> GetFirstBoxPosition() { return mFirstBoxPosition; }

	const int& GetMapX() { return mMapX; }
	const int& GetMapZ() { return mMapZ; }
	const int& GetMaxEnemy() { return mMaxEnemyTroop; }

	XMINT2 GetPlayerPosition() { return mPlayerPosition; }
	std::vector<XMINT2> GetEnemyPosition() { return mEnemyPosition; }

private:
	std::string mFilename;
	char mMap[MapSizeX * MapSizeZ] = {};
	int mMapX = 0;
	int mMapZ = 0;
	int mMaxEnemyTroop = 0;

	XMINT2 mPlayerPosition = XMINT2(0, 0);
	std::vector<XMINT2> mEnemyPosition;

	CObjectType** mpType = nullptr;
	CBoxType** mpBox = nullptr;
	//std::list<XMINT2> mFirstBoxPosition;

	void Init();
	void SetPlayerPosition(XMINT2 p) { mPlayerPosition = p; }
	void SetEnemyPosition(XMINT2 p) { mEnemyPosition.push_back(p); }
};

#endif // !LOADMAP_H_
