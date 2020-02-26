#pragma once

//============================================================================
//=																			 =
//=					ユーザーインターフェース	メニュー					 =
//=																			 =
//============================================================================

#ifndef MENU_H_
#define MENU_H_

class CMenu : public CUI
{
public:
	CMenu();
	~CMenu();

	void Update();
	void Draw();
};

#endif // !MENU_H_
