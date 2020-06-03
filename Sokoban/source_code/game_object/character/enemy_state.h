#pragma once

//============================================================================
//=																			 =
//=							���ۃN���X�@�G�̏��							 =
//=																			 =
//============================================================================

#ifndef ENEMY_STATE_H_
#define ENEMY_STATE_H_

class CEnemyState
{
public:
	//���쎞��
	virtual void ActionTime() {}

	//����
	virtual CAction Action(CEnemyTroop* p) = 0;

	//�s�����Ԃ̕\��
	virtual void DrawTime() {}
};

#endif // !ENEMY_STATE_H_


