#pragma once

//============================================================================
//=																			 =
//=							�N���X�@���[�h�}�b�v							 =
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
			MessageBox(NULL, "�ǂݍ��ݎ��s", "�G���[", MB_OK);
		}

		//�}�b�v�T�C�Y���擾
		mMapX = fgetc(file);
		mMapZ = fgetc(file);
		
		//�������m��
		mpType = new CObjectType*[mMapZ];

		for (int x = 0; x < mMapZ; x++)
			mpType[x] = new CObjectType[mMapX];

		//������
		for (int i = 0; i < mMapX * mMapZ; i++)
			mpType[i / mMapX][i % mMapX] = CObjectType::None;

		fgets(mMap, MapSizeX * MapSizeZ, file);

		//�}�b�v�̃I�u�W�F�N�g�̎��
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
