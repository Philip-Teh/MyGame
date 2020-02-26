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

	void TabCancel();
};

//}
#endif


