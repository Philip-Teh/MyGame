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
private:
	std::string mTexture;
	CPolygon* mpPolygon = nullptr;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

#endif // !RESULT_H_
