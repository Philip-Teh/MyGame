#pragma once

//============================================================================
//=																			 =
//=				���[�U�[�C���^�[�t�F�[�X	�X�e�v�b�v						 =
//=																			 =
//============================================================================

#ifndef STEP_H_
#define STEP_H_

class CStep : public CUI
{
public:
	CStep();
	~CStep();

	void Update();
	void Draw(int step);

};

#endif // !STEP_H_