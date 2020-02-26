#pragma once

//============================================================================
//=																			 =
//=							’ŠÛƒNƒ‰ƒX@“G‚Ìó‘Ô							 =
//=																			 =
//============================================================================

#ifndef ENEMY_STATE_H_
#define ENEMY_STATE_H_

class CEnemyState
{
public:
	//“®ìŠÔ
	virtual void ActionTime() {};
	//“®ì
	virtual CAction Action(CEnemyTroop* p) = 0;
};

#endif // !ENEMY_STATE_H_


