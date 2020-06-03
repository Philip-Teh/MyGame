#pragma once

//============================================================================
//=																			 =
//=					ユーザーインターフェース	リプレイ					 =
//=																			 =
//============================================================================

#ifndef REPLAY_H
#define REPLAY_H

//namespace UI
//{

	class CReplay : public CUI
	{
	public:
		CReplay();
		~CReplay();

		void Update();
		void Draw();
	};
//}
#endif


