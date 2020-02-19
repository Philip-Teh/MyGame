#ifndef MAIN_H_
#define MAIN_H_

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define NOMINMAX
#include <windows.h>
#undef NOMINMAX
#include <assert.h>
#include <io.h>
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

#define LAYER0	(0.0f)
#define LAYER1	(0.1f)
#define LAYER2	(0.2f)
#define LAYER3	(0.3f)
#define LAYER4  (0.4f)
#define LAYER5  (0.5f)
#define LAYER6  (0.6f)
#define LAYER7  (0.7f)
#define LAYER8  (0.8f)

#define NUMBER_DIGIT (5)
#define NUMBER_WIDTH (32)
#define NUMBER_SIZEX (320)
#define NUMBER_HEIGHT (32)

#define MapSizeZ (40)
#define MapSizeX (40)

#define MaXStage (3)

#define STATUS_POSITIONX (950.0f)
#define STATUS_POSITIONY (10.0f)
#define HIDDEN_STATUS_POSITIONY (60.0f)

#define STATUS_POLYGONX (100.0f)
#define STATUS_POLYGONY (50.0f)

#define NUMSPACEX (250.0f)
#define NUMSPACEY (10.0f)

#define VK_YEA ('Y')
#define VK_NAY ('N')


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
	Up,
	Down,
	Left,
	Right,
	None,
};

struct CRotation
{
	const float right1 = -1.6f;
	const float down = 0.0f;
	const float left = 1.6f;
	const float up = 3.2f;
	const float right = 4.8f;
	const float down1 = 6.4f;
};

enum class CAction
{
	Idle,
	Move
};

enum class CEnemyAI
{
	Easy,
	Normal,
	Hard,
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

class CExitTrigger
{
public:
	static void SetExit(bool exit) { mExit = exit; }
	static const bool& GetExit() { return mExit; }
private:
	static bool mExit;
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

