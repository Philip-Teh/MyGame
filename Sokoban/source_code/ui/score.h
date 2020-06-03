#pragma once

//============================================================================
//=																			 =
//=					ユーザーインターフェース	スコア						 =
//=																			 =
//============================================================================

#ifndef SCORE_H_
#define SCORE_H_

class CScore : public CUI
{
public:
	CScore();
	~CScore();

	void Update();
	void Draw(int score);
};

#endif // !SCORE_H_