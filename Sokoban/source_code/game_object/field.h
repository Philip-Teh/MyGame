#pragma once

//============================================================================
//=																			 =
//=						 �Q�[���I�u�W�F�N�g�@�t�B�[���h						 =
//=																			 =
//============================================================================

#ifndef FIELD_H_
#define FIELD_H_

class CField : public CGameObject {
public:
	void Init(std::string texture);
	void Uninit();
	void Update();
	void Draw(XMFLOAT3 position, float rotate);

private:
	std::unique_ptr<CShader> mpShader = nullptr;
	CTexture* mpTexture = nullptr;

	ID3D11Buffer* mpVertexBuffer = nullptr;	//���_�o�b�t�@
	ID3D11Buffer* mpIndexBuffer = nullptr;	//�C���f�b�N�X�o�b�t�@

	const XMFLOAT2 mSize = XMFLOAT2(1.0f, 1.0f);
	const XMINT2 mNum = XMINT2(1, 1);

	int mNumVertices = NULL;
};

#endif