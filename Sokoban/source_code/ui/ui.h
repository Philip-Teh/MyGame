#pragma once

//============================================================================
//=																			 =
//=					���ۃN���X�@���[�U�[�C���^�[�t�F�[�X�@					 =
//=																			 =
//============================================================================

#ifndef UI_H_
#define UI_H_

class CUI
{
public:
	virtual ~CUI() {}

	virtual void Update() {}
	virtual void Draw() {}

	virtual const bool& GetKeyUp() { return mKeyUp; }
	virtual const bool& GetKeyDown() { return mKeyDown; }

	virtual void TabCancel() {}

protected:
	std::string mFile = "";
	std::string mFile1 = "";
	std::unique_ptr<CPolygon> mpPolygon = nullptr;
	std::unique_ptr<CPolygon> mpPolygon1 = nullptr;
	std::unique_ptr<CNumDraw> mpNumDraw = nullptr;

	const float mWidth = 640.0f;	//�摜�̕�
	const float mHeight = 480.0f;	//�摜�̍���
	const int mSpeed = 100;			//�B���C���^�[�t�F�[�X�̏o�����x
	const XMFLOAT2 mPosition = XMFLOAT2(350.0f, 100.0f);

	int mMove = 0;
	bool mKeyUp = false;
	bool mKeyDown = false;
	bool mKeyUpDown = false;
};

#endif // !UI_H_

