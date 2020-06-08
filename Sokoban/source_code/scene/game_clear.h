#pragma once

//============================================================================
//=																			 =
//=							シーン　ゲームクリア							 =
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

	const XMFLOAT2 mGameClearSize = XMFLOAT2(700.0f, 270.0f);
	const XMFLOAT2 mCharacterSize = XMFLOAT2(150.0f, 150.0f);
	const XMFLOAT2 mGameClearPos = XMFLOAT2(750.0f, 10.0f);
	const XMFLOAT2 mCharacterPos = XMFLOAT2(200.0f, 310.0f);

	const float mMax = 500.0f;
	const float mSpeed = 10.0f;
	
	float mMove1 = 0.0f, mMove2 = 0.0f;

	//限界までの移動
	float MaxMove(float move);
};

#endif // !RESULT_H_
