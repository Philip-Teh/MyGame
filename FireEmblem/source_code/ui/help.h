#pragma once


#ifndef HELP_H
#define HELP_H

//namespace UI
//{

	class CHelp
	{
	public:
		CHelp();
		~CHelp();

		void Update();
		void Draw();

		void FirstDraw();
		void FirstDrawCancel();
		void SetKeyEnter(bool key) { mKeyEnter = key; }

		const bool& GetPress(void) { return mkeyUp; }
		void TabCancel(void);

	private:
		std::unique_ptr<CPolygon> mpPolygon = nullptr;

		const float mWidth = 640.0f;
		const float mHeight = 480.0f;
		const int mSpeed = 100;
		const XMFLOAT2 mPosition = XMFLOAT2(350.0f, 100.0f);

		int mMove = 0;
		bool mkeyUp = false;
		bool mkeyDown = false;
		bool mkeyUpDown = false;

		int mMoveFirst = 0;
		bool mKeyEnter = false;
	};
//}
#endif


