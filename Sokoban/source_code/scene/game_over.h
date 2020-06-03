#pragma once

//============================================================================
//=																			 =
//=							シーン　ゲームオーバー							=
//=																			 =
//============================================================================

#ifndef GAMEOVER_H
#define GAMEOVER_H

class CGameOver
{

public:
	void Init();
	void Uninit();

	void Update();
	void Draw();

	//ゲームオーバーシーン演出をリセット
	bool ResetShow();

	//ゲームオーバーシーン演出を終了
	bool ShowEnd();

	void SetKey(bool press) { mKeypress = press; }
	bool GetKey() { return mKeypress; }

private:
	std::string mFile[3];
	std::unique_ptr<CPolygon> mpPolygon[3];
	float mMove = 0.0f, mMove1 = 0.0f, mMove2 = 0.0f;
	bool mKeypress = false;

	float MaxMove(float move);
};

#endif
