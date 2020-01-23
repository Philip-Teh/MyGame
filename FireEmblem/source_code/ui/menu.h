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

private:
	std::string mFile[2];
	std::unique_ptr<CPolygon> mpPolygon[2];

	int mMove;
	bool mKeyUp, mKeyDown, mKeyTrigger;
};

#endif // !MENU_H_
