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
	
	//オブジェクトのゲッター
	CObjectType** GetType() { return mpType; }

	//箱のゲッター
	CBoxType** GetBox() { return mpBox; }

	//マップの横幅ゲッター
	const int& GetMapX() { return mMapX; }

	//マップの縦幅のゲッター
	const int& GetMapZ() { return mMapZ; }

	//敵の最大数のゲッター
	const int& GetMaxEnemy() { return mMaxEnemyTroop; }

	XMINT2 GetPlayerPosition() { return mPlayerPosition; }
	std::vector<XMINT2> GetEnemyPosition() { return mEnemyPosition; }

private:
	std::string mFilename = "";
	char mMap[MapSizeX * MapSizeZ] = {};
	int mMapX = 0;
	int mMapZ = 0;
	int mMaxEnemyTroop = 0;

	XMINT2 mPlayerPosition = XMINT2(0, 0);
	std::vector<XMINT2> mEnemyPosition;

	CObjectType** mpType = nullptr;
	CBoxType** mpBox = nullptr;

	void Init();
	void SetPlayerPosition(XMINT2 p) { mPlayerPosition = p; }
	void SetEnemyPosition(XMINT2 p) { mEnemyPosition.push_back(p); }
};

#endif // !LOADMAP_H_
