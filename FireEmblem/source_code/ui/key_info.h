#pragma once

//============================================================================
//=																			 =
//=					ユーザーインターフェース	操作説明					 =
//=																			 =
//============================================================================

#ifndef KEY_INFO_H
#define KEY_INFO_H

//namespace UI
//{

	class CKeyInfo : public CUI
	{
	public:
		CKeyInfo();
		~CKeyInfo();

		void Update();
		void Draw();

		void TabCancel();
	};
//}
#endif


