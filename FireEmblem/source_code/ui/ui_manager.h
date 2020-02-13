#pragma once

#ifndef UIMANAGER_H
#define UIMANAGER_H

	class CUIManager
	{
	public:
		CUIManager();
		~CUIManager();

		void Update();
		void Update(bool enable);
		void DrawStatus(int score, int step);
		void DrawEnemyStatus(int num);
		void DrawStageNum(int num);					//第何番のステージ描画
		void DrawMenu();

		void Appear();

		const bool& GetPress();
		void SetLock(bool lock) { mpPull->SetLock(lock); }

	private:
		std::unique_ptr<CScore> mpScore;
		std::unique_ptr<CStep> mpStep;
		std::unique_ptr<CNumEnemy> mpNumEnemy;
		std::unique_ptr<CPull> mpPull;
		std::unique_ptr<CStageNum> mpStageNum;

		std::unique_ptr<CMenu> mpMenu;
		std::unique_ptr<CHelp> mpHelp;
		std::unique_ptr<CKeyInfo> mpKeyInfo;
	};

#endif
