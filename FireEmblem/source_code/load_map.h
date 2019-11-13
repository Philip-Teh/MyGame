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
	bool Load(int mapID)
	{
		FILE* file;
		std::string mapid = std::to_string(mapID);

		mFilename = "asset/map/map" + mapid + ".bin";

		if ((file = fopen(mFilename.c_str(), "rb")) == nullptr)
		{
			MessageBox(NULL, "�ǂݍ��ݎ��s", "�G���[", MB_OK);
		}
		
		mMapX = fgetc(file);
		mMapZ = fgetc(file);
	}
	
private:
	std::string mFilename;
	int mMapX = 0;
	int mMapZ = 0;
};

#endif // !LOADMAP_H_
