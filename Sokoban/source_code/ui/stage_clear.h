#pragma once

//============================================================================
//=																			 =
//=				���[�U�[�C���^�[�t�F�[�X	�X�e�[�W�N���A					 =
//=																			 =
//============================================================================

#ifndef STAGECLEAR_H
#define STAGECLEAR_H

//namespace StageSystem
//{
	class CStageClear : public CUI
	{
	public:
		CStageClear();
		~CStageClear();

		void Update();
		void Draw();

		//�ʒu���Z�b�g
		void SetMove();

		//�`��I���̏���
		bool DrawCompleted();

	};
//}
#endif
