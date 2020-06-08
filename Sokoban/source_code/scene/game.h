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

	std::unique_ptr<CCamera> mpCamera = nullptr;				//カメラ
	std::unique_ptr<CStageManager> mpStageManager = nullptr;	//ステージマネージャー
	std::unique_ptr<CSkydome> mpSkydome = nullptr;				//スカイドーム
	std::unique_ptr<CMeshfield> mpMeshField = nullptr;			//メッシュフィール

	std::unique_ptr<CGameOver> mpGameOver = nullptr;			//ゲームオーバー
	std::unique_ptr<CReplay> mpReplay = nullptr;				//リプレイ

	bool mGameOver = false;

	//ステージセレクトへ戻す処理
	bool ReturnStageSelect();

	//タイトルへ戻す処理
	bool ReturnTitle();
};

#endif // !GAME_H_

