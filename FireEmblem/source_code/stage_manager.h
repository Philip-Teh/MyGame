#pragma once

//============================================================================
//=																			 =
//=							ステージマネージャー							 =
//=																			 =
//============================================================================

#ifndef STAGEMANAGER_H_
#define STAGEMANAGER_H_

class CStageManager
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	std::unique_ptr<CMap> mpMap;

};

#endif // !STAGEMANAGER_H_
