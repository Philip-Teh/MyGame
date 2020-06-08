#pragma once

//============================================================================
//=																			 =
//=				ユーザーインターフェース	リターンタイトル				 =
//=																			 =
//============================================================================

#ifndef RETURN_TITLE_H
#define RETURN_TITLE_H

//namespace UI
//{

class CReturnTitle : public CUI
{
public:
	CReturnTitle();
	~CReturnTitle();

	void Update();
	void Draw();

	//メニュー退出時の終了処理
	void TabCancel();
};

//}
#endif


