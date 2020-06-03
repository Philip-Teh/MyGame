#pragma once 

//============================================================================
//=																			 =
//=							���͊֘A�@�L�[�{�[�h							 =
//=																			 =
//============================================================================

#ifndef INPUT_H_
#define INPUT_H_

class CInput
{
private:
	static BYTE m_OldKeyState[256];
	static BYTE m_KeyState[256];

public:
	static void Init();
	static void Uninit();
	static void Update();

	//�L�[�������Ă��鎞
	static bool GetKeyPress( BYTE KeyCode );

	//�L�[��������
	static bool GetKeyTrigger( BYTE KeyCode );

};

#endif