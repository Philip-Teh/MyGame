#pragma once

//============================================================================
//=																			 =
//=					���[�U�[�C���^�[�t�F�[�X	�������					 =
//=																			 =
//============================================================================

#ifndef KEY_INFO_H
#define KEY_INFO_H

//namespace UI
//{

	class CKeyInfo : public CUI
	{
	public:
		CKeyInfo();
		~CKeyInfo();

		void Update();
		void Draw();

		//���j���[�ޏo���̏I������
		void TabCancel();
	};
//}
#endif


