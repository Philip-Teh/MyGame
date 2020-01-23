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
	std::string mTexture[3];
	std::unique_ptr<CPolygon> mpPolygon[3];
	int mFrame = 0;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

#endif // !TUTORIAL_H_

