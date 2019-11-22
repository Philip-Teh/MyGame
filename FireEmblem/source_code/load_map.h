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
	void Load(int mapID)
	{
		FILE* file;
		std::string mapid = std::to_string(mapID);

		mFilename = "asset/map/map" + mapid + ".bin";

		if ((file = fopen(mFilename.c_str(), "rb")) == nullptr)
		{
			MessageBox(NULL, "読み込み失敗", "エラー", MB_OK);
		}

		//マップサイズを取得
		mMapX = fgetc(file);
		mMapZ = fgetc(file);
		
		//メモリ確保
		mpType = new CObjectType*[mMapZ];

		for (int x = 0; x < mMapZ; x++)
			mpType[x] = new CObjectType[mMapX];

		//初期化
		for (int i = 0; i < mMapX * mMapZ; i++)
			mpType[i / mMapX][i % mMapX] = CObjectType::None;

		fgets(mMap, MapSizeX * MapSizeZ, file);

		//マップのオブジェクトの種類
		for (int i = 0; i < mMapX * mMapZ; i++)
		{
			switch ((CObjectType)mMap[i])
			{
			case CObjectType::Allies:
				mpType[i / mMapX][i % mMapX] = CObjectType::Allies;
				break;
			case CObjectType::Enemy:
				mpType[i / mMapX][i % mMapX] = CObjectType::Enemy;
				break;
			case CObjectType::Plain:
				mpType[i / mMapX][i % mMapX] = CObjectType::Plain;
				break;
			case CObjectType::Mountain:
				mpType[i / mMapX][i % mMapX] = CObjectType::Mountain;
				break;
			case CObjectType::Forest:
				mpType[i / mMapX][i % mMapX] = CObjectType::Forest;
				break;
			case CObjectType::None:
				mpType[i / mMapX][i % mMapX] = CObjectType::None;
				break;
			default:
				mpType[i / mMapX][i % mMapX] = CObjectType::None;
				break;
			}
		}

		fclose(file);
	}

	void ReleaseMap(void)
	{
		for (int z = 0; z < mMapZ; z++)
			delete[] mpType[z];

		delete[]mpType;
	}
	
	CObjectType** GetType()
	{
		return mpType;
	}

	int GetMapX() { return mMapX; }
	int GetMapZ() { return mMapZ; }

private:
	std::string mFilename;
	char mMap[MapSizeX * MapSizeZ] = {};
	int mMapX = NULL;
	int mMapZ = NULL;

	CObjectType** mpType = nullptr;
};

#endif // !LOADMAP_H_
