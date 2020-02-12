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

private:
	std::unique_ptr<CMap> mpMap;
	std::unique_ptr<CUIManager> mpUIManager;
	std::unique_ptr<CStageClear> mpStageClear;
	bool mStageClear = false;
	int mStage = 0;

	void NextStage();
	void ResetStage();

	void ScoreCaculate();
};

#endif // !STAGEMANAGER_H_
