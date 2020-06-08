#pragma once

//============================================================================
//=																			 =
//=						�Q�[���I�u�W�F�N�g�@�G�t�F�N�g						 =
//=																			 =
//============================================================================

#ifndef EFFECT_H_
#define EFFECT_H_

class CEffect : public CGameObject
{
public:
	void Init(std::string texture, XMFLOAT2 size,int patternmax);
	void Uninit();
	void Update();
	void Draw();

	void Create(XMFLOAT3 position);

private:
	std::unique_ptr<CBillBoard> mpBillBoard = nullptr;

	bool mEnable = false;
	int mFrameCount = 0;	//�J�E���g�t���[��
	int mCreateFrame = 0;	//�N���G�C�g�t���[��
	int mPatternCount = 0;	//�J�E���g�p�^�[��

	int mPatternMax = 0;	//�p�^�[���ő吔
	XMINT2 mSize = XMINT2(0, 0);
};

#endif // !FOREST_H_

