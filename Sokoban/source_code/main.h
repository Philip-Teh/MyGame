#pragma once

//============================================================================
//=																			 =
//=								���C��	�w�b�_�[							 =
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

#define SCREEN_WIDTH	(1280)			// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720)			// �E�C���h�E�̍���

#define WORLD_X		(100)	//���E�̉���
#define WORLD_Z		(100)	//���E�̏c��
#define WORLD_Y		(50)	//���E�̍���

//�`��O��̃��C�A�E�g
#define LAYER0	(0.0f)
#define LAYER1	(0.1f)
#define LAYER2	(0.2f)
#define LAYER3	(0.3f)
#define LAYER4  (0.4f)
#define LAYER5  (0.5f)
#define LAYER6  (0.6f)
#define LAYER7  (0.7f)
#define LAYER8  (0.8f)

#define NUMBER_DIGIT (5)	//�����̌���
#define NUMBER_WIDTH (32)	//�����̕�
#define NUMBER_HEIGHT (32)	//�����̍���
#define NUMBER_SIZEX (320)	//�A�������̕�

#define MapSizeZ (40)	//�}�b�v�̏c
#define MapSizeX (40)	//�}�b�v�̉�

#define MaXStage (3)	//���X�e�[�W��

#define STATUS_POSITIONX (950.0f)		//UI�̉��ʒu
#define STATUS_POSITIONY (10.0f)		//UI�̏c�ʒu
#define HIDDEN_STATUS_POSITIONY (60.0f)	//�B��UI�̏c�ʒu

#define STATUS_POLYGONX (100.0f)	//UI�̕�
#define STATUS_POLYGONY (50.0f)		//UI�̏c

#define NUMSPACEX (250.0f)	//�����̋󂫉��X�y�[�X
#define NUMSPACEY (10.0f)	//�����̋󂫏c�X�y�[�X

#define VK_NUM1 ('1')	//�L�[�{�[�h����1��
#define VK_NUM2 ('2')	//�L�[�{�[�h����2��
#define VK_NUM3 ('3')	//�L�[�{�[�h����3��
#define VK_NUM4 ('4')	//�L�[�{�[�h����4��
#define VK_R    ('R')	//�L�[�{�[�h����R
#define VK_YEA  ('Y')	//�L�[�{�[�h����Y
#define VK_NAY  ('N')	//�L�[�{�[�h����N

HWND GetWindow();

//�I�u�W�F�N�g�̎��
enum class CObjectType
{
	None = 0x00,
	Player = 0x01,

	Goal = 0x04,
	Wall = 0x05,
	Floor = 0x06,

	Enemy = 0x07,
};

//���̏��
enum class CBoxType
{
	Exists = 0x02,
	None = 0x03,
	Moving
};

//�L�����N�^�[�̌���
enum class CDirection
{
	Up,
	Down,
	Left,
	Right,
	None,
};

//�L�����N�^�[�̉�]
struct CRotation
{
	const float right1 = -1.6f;
	const float down = 0.0f;
	const float left = 1.6f;
	const float up = 3.2f;
	const float right = 4.8f;
	const float down1 = 6.4f;
};

//�G�̍s��
enum class CAction
{
	Idle,
	Move
};

//�G�̓�x
enum class CEnemyAI
{
	Easy,
	Normal,
	Hard,
};

//�v�Z�̂��߂̃N���X
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

//�I�������̃g���K�[�������Ă���N���X
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

