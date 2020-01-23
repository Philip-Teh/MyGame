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
	std::string mTexture;
	CAudioClip* m_BGM = nullptr;

	std::unique_ptr<CCamera> mpCamera;
	std::unique_ptr<CStageManager> mpStageManager;
	std::unique_ptr<CSkydome> mpSkydome;
	std::unique_ptr<CMeshfield> mpMeshField;
};

#endif // !GAME_H_

