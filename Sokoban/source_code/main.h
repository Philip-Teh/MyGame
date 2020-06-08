#pragma once

//============================================================================
//=																			 =
//=								メイン	ヘッダー							 =
//=																			 =
//============================================================================

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
#include <memory>

#include <xaudio2.h>

#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "xaudio2.lib")

#define SCREEN_WIDTH	(1280)			// ウインドウの幅
#define SCREEN_HEIGHT	(720)			// ウインドウの高さ

#define WORLD_X		(100)	//世界の横幅
#define WORLD_Z		(100)	//世界の縦幅
#define WORLD_Y		(50)	//世界の高さ

//描画前後のレイアウト
#define LAYER0	(0.0f)
#define LAYER1	(0.1f)
#define LAYER2	(0.2f)
#define LAYER3	(0.3f)
#define LAYER4  (0.4f)
#define LAYER5  (0.5f)
#define LAYER6  (0.6f)
#define LAYER7  (0.7f)
#define LAYER8  (0.8f)

#define NUMBER_DIGIT (5)	//数字の桁数
#define NUMBER_WIDTH (32)	//数字の幅
#define NUMBER_HEIGHT (32)	//数字の高さ
#define NUMBER_SIZEX (320)	//連続数字の幅

#define MapSizeZ (40)	//マップの縦
#define MapSizeX (40)	//マップの横

#define MaXStage (3)	//総ステージ数

#define STATUS_POSITIONX (950.0f)		//UIの横位置
#define STATUS_POSITIONY (10.0f)		//UIの縦位置
#define HIDDEN_STATUS_POSITIONY (60.0f)	//隠しUIの縦位置

#define STATUS_POLYGONX (100.0f)	//UIの幅
#define STATUS_POLYGONY (50.0f)		//UIの縦

#define NUMSPACEX (250.0f)	//数字の空き横スペース
#define NUMSPACEY (10.0f)	//数字の空き縦スペース

#define VK_NUM1 ('1')	//キーボード入力1番
#define VK_NUM2 ('2')	//キーボード入力2番
#define VK_NUM3 ('3')	//キーボード入力3番
#define VK_NUM4 ('4')	//キーボード入力4番
#define VK_R    ('R')	//キーボード入力R
#define VK_YEA  ('Y')	//キーボード入力Y
#define VK_NAY  ('N')	//キーボード入力N

HWND GetWindow();

//オブジェクトの種類
enum class CObjectType
{
	None = 0x00,
	Player = 0x01,

	Goal = 0x04,
	Wall = 0x05,
	Floor = 0x06,

	Enemy = 0x07,
};

//箱の状態
enum class CBoxType
{
	Exists = 0x02,
	None = 0x03,
	Moving
};

//キャラクターの向き
enum class CDirection
{
	Up,
	Down,
	Left,
	Right,
	None,
};

//キャラクターの回転
struct CRotation
{
	const float right1 = -1.6f;
	const float down = 0.0f;
	const float left = 1.6f;
	const float up = 3.2f;
	const float right = 4.8f;
	const float down1 = 6.4f;
};

//敵の行動
enum class CAction
{
	Idle,
	Move
};

//敵の難度
enum class CEnemyAI
{
	Easy,
	Normal,
	Hard,
};

//計算のためのクラス
class CMath
{
public:
	static bool Float3Equal(XMFLOAT3 a,XMFLOAT3 b)
	{
		if (a.x == b.x && a.y == b.y && a.z == b.z) return true;
		else return false;
	}

	static bool Int2Equal(XMINT2 a, XMINT2 b)
	{
		if (a.x == b.x && a.y == b.y)return true;
		else return false;
	}
};

//終了処理のトリガーを持っているクラス
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

