#pragma once

//============================================================================
//=																			 =
//=				���[�U�[�C���^�[�t�F�[�X	�X�e�[�W���Z�b�g				 =
//=																			 =
//============================================================================

#ifndef RESET_H
#define RESET_H

//namespace UI
//{

	class CReset : public CUI
	{
	public:
		CReset();
		~CReset();

		void Update();
		void Draw();

		//���j���[�ޏo���̏I������
		void TabCancel();
	};
//}
#endif


