#pragma once

//============================================================================
//=																			 =
//=								シーン　ゲーム								 =
//=																			 =
//============================================================================

#ifndef GAME_H_
#define GAME_H_

class CGame : public CScene
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	std::string mTexture = "";

	std::unique_ptr<CCamera> mpCamera = nullptr;
	std::unique_ptr<CStageManager> mpStageManager = nullptr;
	std::unique_ptr<CSkydome> mpSkydome = nullptr;
	std::unique_ptr<CMeshfield> mpMeshField = nullptr;

	std::unique_ptr<CGameOver> mpGameOver = nullptr;
	std::unique_ptr<CReplay> mpReplay = nullptr;

	bool mGameOver = false;

	bool ReturnStageSelect();
	bool ReturnTitle();
};

#endif // !GAME_H_

