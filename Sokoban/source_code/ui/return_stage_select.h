#pragma once

//============================================================================
//=																			 =
//=			ユーザーインターフェース	リターンステージリセット			 =
//=																			 =
//============================================================================

#ifndef RETURN_STAGE_SELECT_H
#define RETURN_STAGE_SELECT_H

//namespace UI
//{

	class CReturnStageSelect : public CUI
	{
	public:
		CReturnStageSelect();
		~CReturnStageSelect();

		void Update();
		void Draw();

		//メニュー退出時の終了処理
		void TabCancel();
	};
//}
#endif


