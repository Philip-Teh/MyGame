#pragma once

#ifndef UIMANAGER_H
#define UIMANAGER_H

	class CUIManager
	{
	public:
		CUIManager();
		~CUIManager();

		void Update();
		void DrawStatus(int score, int step,int num);	
		void DrawStageNum(int x, int y, int num);					//第何番のステージ描画
		void DrawMenu();

		bool GetHelp()const { return mpHelp->GetPress(); }
		//bool GetTab()const { return mpKeyInfo->GetPress(); }

	private:
		std::unique_ptr<CScore> mpScore;
		std::unique_ptr<CStep> mpStep;
		std::unique_ptr<CNumEnemy> mpNumEnemy;
		std::unique_ptr<CMenu> mpMenu;
		std::unique_ptr<CHelp> mpHelp;

		//std::unique_ptr<KeyInfo> mpKeyInfo;
	};

#endif
