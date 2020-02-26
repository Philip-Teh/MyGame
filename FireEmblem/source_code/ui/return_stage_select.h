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

		void TabCancel();
	};
//}
#endif


