#pragma once


#ifndef HELP_H
#define HELP_H

//namespace UI
//{

	class CHelp : public CUI
	{
	public:
		CHelp();
		~CHelp();

		void Update();
		void Draw();

		//���j���[�ޏo���̏I������
		void TabCancel();

		//���`��(�`���[�g���A��)
		void FirstDraw();

		//���`��I��
		void FirstDrawCancel();
		void SetKeyEnter(bool key) { mKeyEnter = key; }

	private:
		int mMoveFirst = 0;
		bool mKeyEnter = false;
	};
//}
#endif


