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
		void DrawSN(int x, int y, int num);					//第何番のステージ描画
		void DrawMenu();

		//bool GetTab()const { return mpKeyInfo->GetPress(); }
		//bool GetHelp()const { return mpGameHelp->GetPress(); }
		bool GetKeyUp()const { return mKeyUp; }

	private:
		std::unique_ptr<CScore> mpScore;
		std::unique_ptr<CStep> mpStep;
		std::unique_ptr<CNumEnemy> mpNumEnemy;
		std::unique_ptr<CMenu> mpMenu;
		//std::unique_ptr<KeyInfo> mpKeyInfo;
		//std::unique_ptr<GameHelp> mpGameHelp;
		//std::string mFile;
		int mMove;
		bool mKeyUp, mKeyDown, mKeyUpDown;
	};

#endif
