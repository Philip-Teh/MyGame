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

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
private:
	std::string mTexture[3] = {};
	std::unique_ptr<CPolygon> mpPolygon[3] = {};
	int mFrame = 0;	//表示フレーム
};

#endif // !TITLE_H_

