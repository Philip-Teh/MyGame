#pragma once

//============================================================================
//=																			 =
//=							シーン　ステージセレクト						 =
//=																			 =
//============================================================================

#ifndef STAGE_SELECT_H_
#define STAGE_SELECT_H_

class CStageSelect : public CScene
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	std::string mTexture[2] = {};
	std::unique_ptr<CPolygon> mpPolygon[2] = {};

	std::unique_ptr<CSelectButton> mpSelectButton = nullptr;	//ボタンポインタ

	const float mPositionX = 400.0f;
	const float mWidth = 500.0f;
	const float mHeight = 200.0f;
};

#endif // !STAGE_SELECT_H_

