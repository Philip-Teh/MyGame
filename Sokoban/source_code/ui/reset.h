#pragma once

//============================================================================
//=																			 =
//=				ユーザーインターフェース	ステージリセット				 =
//=																			 =
//============================================================================

#ifndef RESET_H
#define RESET_H

//namespace UI
//{

	class CReset : public CUI
	{
	public:
		CReset();
		~CReset();

		void Update();
		void Draw();

		void TabCancel();
	};
//}
#endif


