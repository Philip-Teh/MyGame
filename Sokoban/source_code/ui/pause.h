#pragma once

//============================================================================
//=																			 =
//=					ユーザーインターフェース	ポース						 =
//=																			 =
//============================================================================

#ifndef PAUSE_H
#define PAUSE_H

//namespace UI
//{

	class CPause : public CUI
	{
	public:
		CPause();
		~CPause();

		void Update();
		void Draw();
	};
//}
#endif


