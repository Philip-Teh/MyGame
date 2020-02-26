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

		void TabCancel();
	};
//}
#endif


