#pragma once

//============================================================================
//=																			 =
//=				ユーザーインターフェース	ステージナンバー				 =
//=																			 =
//============================================================================

#ifndef STAGE_NUM_H_
#define STAGE_NUM_H_

class CStageNum : public CUI
{
public:
	CStageNum();
	~CStageNum();

	void Update();
	void Draw(int num);

private:
	const float mSize = 2.0f;
};

#endif // !STAGE_NUM_H_