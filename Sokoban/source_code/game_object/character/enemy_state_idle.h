#pragma once

//============================================================================
//=																			 =
//=								敵の状態　待機								 =
//=																			 =
//============================================================================

#ifndef ENEMY_STATE_IDLE_H_
#define ENEMY_STATE_IDLE_H_

class CEnemyStateIdle : public CEnemyState
{
public:
	void ActionTime();
	CAction Action(CEnemyTroop* p);
	
	const int& GetTime() { return mRand; }

private:
	int mRand = 0;
	int mFrame = 0;
};

#endif // !ENEMY_STATE_IDLE_H_




