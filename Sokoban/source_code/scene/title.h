#pragma once

//============================================================================
//=																			 =
//=								�V�[���@�^�C�g��							 =
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
	int mFrame = 0;	//�\���t���[��
};

#endif // !TITLE_H_

