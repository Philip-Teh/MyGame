#pragma once

//============================================================================
//=																			 =
//=							シーン　チュートリアル							 =
//=																			 =
//============================================================================

#ifndef TUTORIAL_H_
#define TUTORIAL_H_

class CTutorial : public CScene
{

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
private:
	std::string mTexture = "";
	std::unique_ptr<CPolygon> mpPolygon = nullptr;
	int mFrame = 0;
};

#endif // !TUTORIAL_H_

