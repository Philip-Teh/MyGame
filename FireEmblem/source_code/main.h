#ifndef MAIN_H_
#define MAIN_H_

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define NOMINMAX
#include <windows.h>
#undef NOMINMAX
#include <assert.h>
#include <vector>
#include <typeinfo>
#include <list>
#include <map>
#include <string>

#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "xaudio2.lib")

#define SCREEN_WIDTH	(1280)			// ウインドウの幅
#define SCREEN_HEIGHT	(720)			// ウインドウの高さ

#define WORLD_X		(100)
#define WORLD_Z		(100)
#define WORLD_Y		(50)

#define MapSizeZ (40)
#define MapSizeX (40)

HWND GetWindow();

enum class CObjectType
{
	Allies = 0x0A,
	Enemy = 0x0E,

	Plain = 0x01,
	Mountain = 0x02,
	Forest = 0x03,

	None = 0x00,
};

class CScreen
{
public:
	static int AdjustX() { return SCREEN_WIDTH / 1920; }
	static int AdjustY() { return SCREEN_HEIGHT / 1080; }
};

//#include "lib/cereal/cereal.hpp"
//#include "lib/cereal/archives/json.hpp"
//#include <fstream>
//
//struct VECTOR3
//{
//	float x, y, z;
//	template<class Archive>
//	void serialize(Archive& archive)
//	{
//		archive(CEREAL_NVP(x), CEREAL_NVP(y), CEREAL_NVP(z));
//	}
//};

#endif

