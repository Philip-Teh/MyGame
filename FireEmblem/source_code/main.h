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

HWND GetWindow();

enum class CObjectType
{
	Allies,
	Enemy,
	Mountain,
	Forest,
	Plain,
	None,
};

#endif

