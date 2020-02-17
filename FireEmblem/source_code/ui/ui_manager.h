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

		const bool& GetReturn() { return mpReturn->GetPress(); }
		void ReturnNay() { mpReturn->TabCancel(); }

		const bool& GetReset() { return mpReset->GetPress(); }
		void ResetNay() { mpReset->TabCancel(); }

	private:
		std::unique_ptr<CScore> mpScore = nullptr;
		std::unique_ptr<CStep> mpStep = nullptr;
		std::unique_ptr<CNumEnemy> mpNumEnemy = nullptr;
		std::unique_ptr<CPull> mpPull = nullptr;
		std::unique_ptr<CStageNum> mpStageNum = nullptr;

		std::unique_ptr<CMenu> mpMenu = nullptr;
		std::unique_ptr<CHelp> mpHelp = nullptr;
		std::unique_ptr<CKeyInfo> mpKeyInfo = nullptr;
		std::unique_ptr<CPause> mpPause = nullptr;
		std::unique_ptr<CReturn> mpReturn = nullptr;

		std::unique_ptr<CReset> mpReset = nullptr;
		std::unique_ptr<CExit> mpExit = nullptr;

	};

#endif
