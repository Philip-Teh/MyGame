#pragma once

//============================================================================
//=																			 =
//=				���[�U�[�C���^�[�t�F�[�X	�X�e�[�W�I�[�o�[				 =
//=																			 =
//============================================================================

#ifndef STAGEOVER_H
#define STAGEOVER_H

//namespace StageSystem
//{
	class CStageOver : public CUI
	{
	public:
		CStageOver();
		~CStageOver();

		void Update();
		void Draw();
		
		//�ʒu���Z�b�g
		void SetMove();

		//�`��I���̏���
		bool DrawCompleted();

	};
//}
#endif
