#pragma once

//============================================================================
//=																			 =
//=				ユーザーインターフェース	ステージクリア					 =
//=																			 =
//============================================================================

#ifndef STAGECLEAR_H
#define STAGECLEAR_H

//namespace StageSystem
//{
	class CStageClear : public CUI
	{
	public:
		CStageClear();
		~CStageClear();

		void Update();
		void Draw();

		//位置リセット
		void SetMove();

		//描画終了の処理
		bool DrawCompleted();

	};
//}
#endif
