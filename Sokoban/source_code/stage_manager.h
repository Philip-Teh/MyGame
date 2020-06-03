#pragma once

//============================================================================
//=																			 =
//=							ステージマネージャー							 =
//=																			 =
//============================================================================

#ifndef STAGEMANAGER_H_
#define STAGEMANAGER_H_

class CStageManager : public CGameObject
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	//ステージセレクトへ戻すゲッターとセッター
	const bool& GetReturn() { return mpUIManager->GetReturn(); }
	void ReturnNay() { mpUIManager->ReturnNay(); }

	//タイトルトへ戻すゲッターとセッター
	const bool& GetReturnTitle() { return mpUIManager->GetReturnTitle(); }
	void ReturnTitleNay() { mpUIManager->ReturnTitleNay(); }

	//ステージ再ロード
	void ResetStage();

private:
	//マップを管理するポインタ
	std::unique_ptr<CMap> mpMap;

	//ユーザーインターフェースを管理するポインタ
	std::unique_ptr<CUIManager> mpUIManager;

	//ステージクリアシーンを管理するポインタ
	std::unique_ptr<CStageClear> mpStageClear;

	//ステージオーバーシーンを管理するポインタ
	std::unique_ptr<CStageOver> mpStageOver;

	//敵が現れる判定
	bool mEnemyAppear = false;

	//ステージがクリアした判定
	bool mStageClear = false;

	//スコアが加算される判定
	bool mPlusScore = false;

	//現在のステージ
	int mStage = 0;

	//次のステージのプログラム
	void NextStage();

	//スコアを加算
	void ScoreCaculate();
};

#endif // !STAGEMANAGER_H_
