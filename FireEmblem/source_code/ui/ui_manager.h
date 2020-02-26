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
		void FirstDrawHelp() { mpHelp->FirstDraw(); }
		void SetKeyEnter(bool key) { mpHelp->SetKeyEnter(key); }

		const bool& GetPress();
		void SetLock(bool lock) { mpPull->SetLock(lock); }

		const bool& GetReturn() { return mpReturn->GetKeyUp(); }
		void ReturnNay() { mpReturn->TabCancel(); }

		const bool& GetReturnTitle() { return mpTitle->GetKeyUp(); }
		void ReturnTitleNay() { mpTitle->TabCancel(); }

		const bool& GetReset() { return mpReset->GetKeyUp(); }
		void ResetNay() { mpReset->TabCancel(); }

		const bool& GetExit() { return mpExit->GetKeyUp(); }

	private:
		std::unique_ptr<CScore> mpScore = nullptr;
		std::unique_ptr<CStep> mpStep = nullptr;
		std::unique_ptr<CNumEnemy> mpNumEnemy = nullptr;
		std::unique_ptr<CPull> mpPull = nullptr;
		std::unique_ptr<CStageNum> mpStageNum = nullptr;

		std::unique_ptr<CMenu> mpMenu = nullptr;
		std::unique_ptr<CHelp> mpHelp = nullptr;
		std::unique_ptr<CKeyInfo> mpKeyInfo = nullptr;
		std::unique_ptr<CReturnTitle> mpTitle = nullptr;
		std::unique_ptr<CReturnStageSelect> mpReturn = nullptr;

		std::unique_ptr<CReset> mpReset = nullptr;
		std::unique_ptr<CExit> mpExit = nullptr;

		std::unique_ptr<CPause> mpPause = nullptr;

	};

#endif
