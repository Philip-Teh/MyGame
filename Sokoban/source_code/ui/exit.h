#pragma once

//============================================================================
//=																			 =
//=					ユーザーインターフェース	終了						 =
//=																			 =
//============================================================================

#ifndef EXIT_H
#define EXIT_H

//namespace UI
//{

	class CExit : public CUI
	{
	public:
		CExit();
		~CExit();

		void Update();
		void Draw();

		//メニュー退出時の終了処理
		void TabCancel();
	};
//}
#endif


