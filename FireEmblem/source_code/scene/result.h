#pragma once

//============================================================================
//=																			 =
//=								シーン　リザルト							 =
//=																			 =
//============================================================================

#ifndef RESULT_H_
#define RESULT_H_

class CResult : public CScene
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
