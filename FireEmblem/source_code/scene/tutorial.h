#pragma once

//============================================================================
//=																			 =
//=								シーン　チュートリアル						 =
//=																			 =
//============================================================================

#ifndef TUTORIAL_H_
#define TUTORIAL_H_

class CTutorial : public CScene
{
private:
	std::string mTexture;
	std::unique_ptr<CPolygon> mpPolygon;
	int mFrame = 0;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

#endif // !TUTORIAL_H_

