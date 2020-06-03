#pragma once 

//============================================================================
//=																			 =
//=							入力関連　キーボード							 =
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

	//キーを押している時
	static bool GetKeyPress( BYTE KeyCode );

	//キーを押す時
	static bool GetKeyTrigger( BYTE KeyCode );

};

#endif