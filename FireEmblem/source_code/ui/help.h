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

		void TabCancel();

		void FirstDraw();
		void FirstDrawCancel();
		void SetKeyEnter(bool key) { mKeyEnter = key; }

	private:
		int mMoveFirst = 0;
		bool mKeyEnter = false;
	};
//}
#endif


