#pragma once

//============================================================================
//=																			 =
//=			���[�U�[�C���^�[�t�F�[�X	���^�[���X�e�[�W���Z�b�g			 =
//=																			 =
//============================================================================

#ifndef RETURN_STAGE_SELECT_H
#define RETURN_STAGE_SELECT_H

//namespace UI
//{

	class CReturnStageSelect : public CUI
	{
	public:
		CReturnStageSelect();
		~CReturnStageSelect();

		void Update();
		void Draw();

		//���j���[�ޏo���̏I������
		void TabCancel();
	};
//}
#endif


