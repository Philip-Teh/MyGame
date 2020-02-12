#pragma once

#ifndef POLYGON_H_
#define POLYGON_H_

class CPolygon {
public:
	void Init(std::string file, XMFLOAT3 position, float sizeX, float sizeY);
	void Init(std::string file, float sizeX, float sizeY);
	void Uninit();
	void Update(XMFLOAT3 position);
	void Draw();
	void Draw(XMFLOAT3 position);
	void Draw(XMFLOAT3 position,int tx, int ty, int tw, int th);

private:
	VERTEX_3D mVertex[4];
	XMFLOAT3 mPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);
	ID3D11Buffer* mpVertexBuffer = nullptr;
	CShader* mpShader = nullptr;
	CTexture* mpTexture = nullptr;
	XMFLOAT2 mSize = XMFLOAT2(0.0f, 0.0f);
};

#endif