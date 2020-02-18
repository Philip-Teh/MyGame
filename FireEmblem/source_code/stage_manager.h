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

	const bool& GetReturn() { return mpUIManager->GetReturn(); }
	void ReturnNay() { mpUIManager->ReturnNay(); }

	const bool& GetReturnTitle() { return mpUIManager->GetReturnTitle(); }
	void ReturnTitleNay() { mpUIManager->ReturnTitleNay(); }

	void ResetStage();

private:
	std::unique_ptr<CMap> mpMap;
	std::unique_ptr<CUIManager> mpUIManager;
	std::unique_ptr<CStageClear> mpStageClear;

	bool mEnemyAppear = false;
	bool mStageClear = false;
	bool mPlusScore = false;
	int mStage = 0;

	void NextStage();
	void ScoreCaculate();
};

#endif // !STAGEMANAGER_H_
