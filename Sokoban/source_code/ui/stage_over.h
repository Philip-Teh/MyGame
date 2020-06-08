#pragma once

//============================================================================
//=																			 =
//=				ユーザーインターフェース	ステージオーバー				 =
//=																			 =
//============================================================================

#ifndef STAGEOVER_H
#define STAGEOVER_H

//namespace StageSystem
//{
	class CStageOver : public CUI
	{
	public:
		CStageOver();
		~CStageOver();

		void Update();
		void Draw();
		
		//位置リセット
		void SetMove();

		//描画終了の処理
		bool DrawCompleted();

	};
//}
#endif
