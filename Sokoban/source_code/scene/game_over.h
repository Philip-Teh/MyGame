#pragma once

//============================================================================
//=																			 =
//=							�V�[���@�Q�[���I�[�o�[							=
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

	//�Q�[���I�[�o�[�V�[�����o�����Z�b�g
	bool ResetShow();

	//�Q�[���I�[�o�[�V�[�����o���I��
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
