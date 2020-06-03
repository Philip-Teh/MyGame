#pragma once

//============================================================================
//=																			 =
//=						ゲームオブジェクト　スカイドーム					 =
//=																			 =
//============================================================================

#ifndef SKYDOME_H_
#define SKYDOME_H_

class CSkydome : public CGameObject 
{

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11Buffer* m_IndexBuffer = nullptr;

	VERTEX_3D* Vertex = nullptr;
	unsigned short* Index = nullptr;
	unsigned short NumVertex = 0;
	unsigned short NumIndex = 0;

	CTexture* m_Texture = nullptr;
	std::unique_ptr<CShader> mpShader = nullptr;

	XMVECTOR mQuaternion = XMVectorZero();

};

#endif