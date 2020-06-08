#pragma once

//============================================================================
//=																			 =
//=					���[�U�[�C���^�[�t�F�[�X	�G�̐�						 =
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

	//�B���C���^�[�t�F�[�X��\��
	void Appear() { mKeyDown = true; }

private:
	const int mMaxMove = 40;
	const int mSpeed = 5;
};

#endif // !NUMENEMY_H_