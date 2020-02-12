#pragma once

#ifndef ENEMY_STATE_H_
#define ENEMY_STATE_H_

class CEnemyState
{
public:
	virtual void ActionTime() = 0;
	virtual CAction Action(CEnemyTroop* p) = 0;
};

#endif // !ENEMY_STATE_H_


