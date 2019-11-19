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
private:
	std::string mTexture;
	CAudioClip* m_BGM = nullptr;
};

#endif // !GAME_H_

