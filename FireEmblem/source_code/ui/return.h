#pragma once


#ifndef RETURN_H
#define RETURN_H

//namespace UI
//{

	class CReturn
	{
	public:
		CReturn();
		~CReturn();

		void Update();
		void Draw();

		const bool& GetPress(void) { return mkeyUp; }
		void TabCancel(void);

	private:
		std::string mFile = "";
		std::unique_ptr<CPolygon> mpPolygon = nullptr;

		const float mWidth = 640.0f;
		const float mHeight = 480.0f;
		const int mSpeed = 100;
		const XMFLOAT2 mPosition = XMFLOAT2(350.0f, 100.0f);

		int mMove = 0;
		bool mkeyUp = false;
		bool mkeyDown = false;
		bool mkeyUpDown = false;
	};
//}
#endif


