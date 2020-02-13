#pragma once


#ifndef KEY_INFO_H
#define KEY_INFO_H

//namespace UI
//{

	class CKeyInfo
	{
	public:
		CKeyInfo();
		~CKeyInfo();

		void Update();
		void Draw();

		const bool& GetPress(void) { return mkeyUp; }
		void TabCancel(void);

	private:
		std::string mFile = "";
		std::unique_ptr<CPolygon> mpPolygon = nullptr;

		int mMove = 0;
		bool mkeyUp = false;
		bool mkeyDown = false;
		bool mkeyUpDown = false;
	};
//}
#endif


