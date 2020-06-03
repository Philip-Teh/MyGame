#pragma once

//============================================================================
//=																			 =
//=								ìGÇÃèÛë‘Å@à⁄ìÆ								 =
//=																			 =
//============================================================================

#ifndef ENEMY_STATE_MOVE_H_
#define ENEMY_STATE_MOVE_H_


class CEnemyStateMove : public CEnemyState
{
public:
	void ActionTime();
	CAction Action(CEnemyTroop* p);

private:
	int mRand = 0;
	int mFrame = 0;
};

#endif // !ENEMY_STATE_MOVE_H_
