#pragma once

//============================================================================
//=																			 =
//=					�Q�[���I�u�W�F�N�g�@���b�V���t�B�[���h					 =
//=																			 =
//============================================================================

#ifndef MESHFIELD_H_
#define MESHFIELD_H_

class CMeshfield : public CGameObject {
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	float GetHeight(XMFLOAT3 position);

private:
	ID3D11Buffer* m_VertexBuffer = nullptr;	//���_�o�b�t�@
	ID3D11Buffer* m_IndexBuffer = nullptr;	//�C���f�b�N�X�o�b�t�@

	VERTEX_3D* Vertex = nullptr;
	unsigned short* Index = nullptr;
	unsigned short NumVertex = NULL;
	unsigned short NumIndex = NULL;

	float sizex = NULL, sizez = NULL;
	int numx = NULL, numz = NULL;

	CTexture* m_Texture = nullptr;
	std::unique_ptr<CShader> mpShader = nullptr;
};

#endif
