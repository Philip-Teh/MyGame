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
		
		void SetMove();
		bool DrawCompleted();

	};
//}
#endif
