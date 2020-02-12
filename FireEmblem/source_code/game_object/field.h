#pragma once

#ifndef FIELD_H_
#define FIELD_H_

class CField : public CGameObject {
public:
	void Init(std::string texture);
	void Init(std::string texture, float x, float z,XMFLOAT3 rgb);
	void Uninit();
	void Update();
	void Draw(XMFLOAT3 position, float rotate);

private:
	ID3D11Buffer* mpVertexBuffer = nullptr;
	ID3D11Buffer* mpIndexBuffer = nullptr;
	std::unique_ptr<CShader> mpShader = nullptr;
	CTexture* mpTexture = nullptr;

	int mNumVertices = NULL;
	const XMFLOAT2 mSize = XMFLOAT2(1.0f, 1.0f);
	XMINT2 mNum = XMINT2(1, 1);
};

#endif