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

		const bool& GetPress(void) { return mkeyUp; }
		void TabCancel(void);

	private:
		std::unique_ptr<CPolygon> mpPolygon;
		int mMove;
		bool mkeyUp, mkeyDown, mkeyUpDown;
	};
//}
#endif


