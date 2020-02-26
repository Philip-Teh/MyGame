#pragma once

//============================================================================
//=																			 =
//=					ユーザーインターフェース	敵の数						 =
//=																			 =
//============================================================================

#ifndef NUMENEMY_H_
#define NUMENEMY_H_

class CNumEnemy : public CUI
{
public:
	CNumEnemy();
	~CNumEnemy();

	void Update();
	void Draw(int num);

	void Appear() { mKeyDown = true; }

private:
	const int mMaxMove = 40;
	const int mSpeed = 5;
};

#endif // !NUMENEMY_H_