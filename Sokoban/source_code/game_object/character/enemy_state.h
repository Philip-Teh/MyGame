#pragma once

//============================================================================
//=																			 =
//=							抽象クラス　敵の状態							 =
//=																			 =
//============================================================================

#ifndef ENEMY_STATE_H_
#define ENEMY_STATE_H_

class CEnemyState
{
public:
	//動作時間
	virtual void ActionTime() {}

	//動作
	virtual CAction Action(CEnemyTroop* p) = 0;

	//行動時間の表示
	virtual void DrawTime() {}
};

#endif // !ENEMY_STATE_H_


