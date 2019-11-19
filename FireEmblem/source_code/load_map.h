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
		
		mMapX = fgetc(file);
		mMapZ = fgetc(file);

		mType = new CObjectType*[mMapZ];

		for (int x = 0; x < mMapZ; x++)
			mType[x] = new CObjectType[mMapX];

		fgets(mMap, MapSizeX * MapSizeZ, file);

		for (int i = 0; i < mMapX * mMapZ; i++)
		{
			switch ((CObjectType)mMap[i])
			{
			case CObjectType::Allies:
				mType[i / mMapX][i % mMapX] = CObjectType::Allies;
				break;
			case CObjectType::Enemy:
				mType[i / mMapX][i % mMapX] = CObjectType::Enemy;
				break;
			case CObjectType::Plain:
				mType[i / mMapX][i % mMapX] = CObjectType::Plain;
				break;
			case CObjectType::Mountain:
				mType[i / mMapX][i % mMapX] = CObjectType::Mountain;
				break;
			case CObjectType::Forest:
				mType[i / mMapX][i % mMapX] = CObjectType::Forest;
				break;
			case CObjectType::None:
				mType[i / mMapX][i % mMapX] = CObjectType::None;
				break;
			default:
				mType[i / mMapX][i % mMapX] = CObjectType::None;
				break;
			}
		}

		fclose(file);
	}

	void ReleaseMap(void)
	{
		for (int z = 0; z < mMapZ; z++)
			delete[] mType[z];

		delete[]mType;
	}
	
	CObjectType** GetType()
	{
		return mType;
	}

	int GetMapX() { return mMapX; }
	int GetMapZ() { return mMapZ; }

private:
	std::string mFilename;
	char mMap[MapSizeX * MapSizeZ] = {};
	int mMapX = 0;
	int mMapZ = 0;

	CObjectType** mType = nullptr;
};

#endif // !LOADMAP_H_
