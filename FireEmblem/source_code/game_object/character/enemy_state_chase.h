#pragma once

//============================================================================
//=																			 =
//=								ìGÇÃèÛë‘Å@í«ê’								 =
//=																			 =
//============================================================================

#ifndef ENEMY_STATE_CHASE_H_
#define ENEMY_STATE_CHASE_H_

class CEnemyStateChase : public CEnemyState
{
public:
	void ActionTime();
	CAction Action(CEnemyTroop* p);

private:
	int mRand = 0;
	int mFrame = 0;
};

#endif // !ENEMY_STATE_CHASE_H_




