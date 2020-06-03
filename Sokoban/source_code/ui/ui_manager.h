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

		//スコアとステップの描画
		void DrawStatus(int score, int step);

		//敵の数の描画
		void DrawEnemyStatus(int num);

		//ステージナンバーの描画
		void DrawStageNum(int num);		

		//メニューの描画
		void DrawMenu();

		//敵の数を表すUIの表示
		void Appear();

		//チュートリアルのUI表示
		void FirstDrawCancel() { mpHelp->FirstDrawCancel(); }
		void FirstDrawHelp() { mpHelp->FirstDraw(); }
		void SetKeyEnter(bool key) { mpHelp->SetKeyEnter(key); }

		//メニューを開く判定
		const bool& GetPress(){	return mpMenu->GetKeyUp(); }

		//引くことの鍵をかけるセッター
		void SetLock(bool lock) { mpPull->SetLock(lock); }

		//ステージセレクトに戻すセッターとゲッター
		const bool& GetReturn() { return mpReturn->GetKeyUp(); }
		void ReturnNay() { mpReturn->TabCancel(); }

		//タイトルに戻すセッターとゲッター
		const bool& GetReturnTitle() { return mpTitle->GetKeyUp(); }
		void ReturnTitleNay() { mpTitle->TabCancel(); }

		//ステージリロードのセッターとゲッター
		const bool& GetReset() { return mpReset->GetKeyUp(); }
		void ResetNay() { mpReset->TabCancel(); }

		//ゲームを終了するゲッター
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
