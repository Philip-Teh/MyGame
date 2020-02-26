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
		
		void SetMove();
		bool DrawCompleted();

	};
//}
#endif
