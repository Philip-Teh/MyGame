#pragma once

//============================================================================
//=																			 =
//=								シーン　クリア								 =
//=																			 =
//============================================================================

#ifndef GAME_CLEAR_H_
#define GAME_CLEAR_H_

class CGameClear : public CScene
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	std::string mTexture[3];
	std::unique_ptr<CPolygon> mpPolygon[3];
	float mMove, mMove1, mMove2;
	float MaxMove(float move);
};

#endif // !RESULT_H_
