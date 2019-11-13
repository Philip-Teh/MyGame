#pragma once

//============================================================================
//=																			 =
//=									 Map									 =
//=																			 =
//============================================================================

#ifndef MAP_H_
#define MAP_H_

#define MapSizeZ (40)
#define MapSizeX (40)

class CMap
{
public:
	CMap();
	~CMap();
	void Update();
	void Draw();

private:
	std::string mMapData[MapSizeZ * MapSizeX];
	CObjectType** mObjectType;
	int mMapX = 0;
	int mMapZ = 0;
};

#endif // !MAP_H_
