#pragma once

//============================================================================
//=																			 =
//=								シーン　タイトル							 =
//=																			 =
//============================================================================

#ifndef TITLE_H_
#define TITLE_H_

class CTitle : public CScene
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

#endif // !TITLE_H_

