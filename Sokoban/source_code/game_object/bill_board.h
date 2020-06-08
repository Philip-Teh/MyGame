#pragma once

//============================================================================
//=																			 =
//=						�Q�[���I�u�W�F�N�g�@�r���{�[�h						 =
//=																			 =
//============================================================================

#ifndef BILLBOARD_H_
#define BILLBOARD_H_

class CBillBoard : public CGameObject
{

public:
	void Init(std::string texture, float sizex, float sizey);
	void Init(std::string texture, XMFLOAT2 size);
	void Uninit();
	void Draw(XMFLOAT3 position);
	void Draw(XMFLOAT3 position, int tx, int ty, int tw, int th);

private:
	CTexture* mpTexture = nullptr;
	std::unique_ptr<CShader> mpShader = nullptr;
	std::unique_ptr<CPolygon> mpPolygon = nullptr;

	ID3D11Buffer* mpVertexBuffer = nullptr;	//���_�o�b�t�@
	ID3D11Buffer* mpIndexBuffer = nullptr;	//�C���f�b�N�X�o�b�t�@

	CCamera* mpCamera = nullptr;
};



#endif // BILLBOARD_H_
