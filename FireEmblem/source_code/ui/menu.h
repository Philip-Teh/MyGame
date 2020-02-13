#pragma once

#ifndef MENU_H_
#define MENU_H_

class CMenu
{
public:
	CMenu();
	~CMenu();
	void Update();
	void Draw();

	bool GetKeyUp()const { return mKeyUp; }
	bool GetKeyDown()const { return mKeyDown; }

private:
	std::string mFile[2];
	std::unique_ptr<CPolygon> mpPolygon[2];

	int mMove = 0;
	bool mKeyUp = false;
	bool mKeyDown = false;
	bool mKeyTrigger = false;
};

#endif // !MENU_H_
