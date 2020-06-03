#pragma once

#ifndef GAMESTATUS_H_
#define GAMESTATUS_H_

//============================================================================
//=																			 =
//=							�Q�[�����ł̃X�e�[�^�X							 =
//=																			 =
//============================================================================

class CGameStatus
{
public:
	static void SetScore(int score) { mScore = score; }
	static int GetScore(void) { return mScore; }
	static void PlusScore(int score) { mScore += score; }

	static void SetStageClear(int stage) { mStageClear = stage; }
	static int GetStageClear(void) { return mStageClear; }

	static void SetStageChoose(int stage) { mStageChoose = stage; }
	static int GetStageChoose(void) { return mStageChoose; }

	static void SetGameClear(bool clear) { mGameClear = clear; }
	static bool GetGameClear(void) { return mGameClear; }

	static void SetGameOver(bool clear) { mGameOver = clear; }
	static bool GetGameOver(void) { return mGameOver; }

private:
	static int mScore;			//�X�R�A
	static int mStageClear;		//�N���A�����X�e�[�W
	static int mStageChoose;	//�I�������V�[��
	static bool mGameClear;		//�Q�[���N���A
	static bool mGameOver;		//�Q�[���I�[�o�[
};


#endif // !GAMESTATUS_H_

