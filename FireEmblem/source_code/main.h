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
#include <ctime>

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

#define MaXStage (2)

HWND GetWindow();

enum class CObjectType
{
	None = 0x00,
	Player = 0x01,

	Goal = 0x04,
	Wall = 0x05,
	Floor = 0x06,

	Enemy = 0x07,
};

enum class CBoxType
{
	Exists = 0x02,
	None = 0x03,
	Moving
};

enum class CDirection
{
	Up = 110,
	Down = 0,
	Left = -55,
	Right = 55,
};

class CMath
{
public:
	template<class T>
	static const T & Min(const T & a, const T & b)
	{
		return (b < a) ? b : a;
	}

	static bool Float3Equal(XMFLOAT3 a,XMFLOAT3 b)
	{
		if (a.x == b.x && a.y == b.y && a.z == b.z)
			return true;
		else
			return false;
	}
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

