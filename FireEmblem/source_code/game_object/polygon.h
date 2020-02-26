#pragma once

//============================================================================
//=																			 =
//=							ï`âÊä÷òAÅ@É|ÉäÉSÉì								 =
//=																			 =
//============================================================================

#ifndef POLYGON_H_
#define POLYGON_H_

class CPolygon {
public:
	void Init(std::string file, XMFLOAT3 position, float sizeX, float sizeY);
	void Init(std::string file, float sizeX, float sizeY);
	void InitBillBoard(std::string file, float sizeX, float sizeY);
	void Uninit();
	void Update(XMFLOAT3 position);
	void Draw();
	void Draw(XMFLOAT3 position);
	void Draw(XMFLOAT3 position,int tx, int ty, int tw, int th);
	void DrawBillBoard(XMFLOAT3 position, int tx, int ty, int tw, int th);

private:
	VERTEX_3D mVertex[4] = {};
	XMFLOAT3 mPosition = {};

	ID3D11Buffer* mpVertexBuffer = nullptr;
	ID3D11Buffer* mpIndexBuffer = nullptr;

	std::unique_ptr<CShader> mpShader = nullptr;
	CTexture* mpTexture = nullptr;
	XMFLOAT2 mSize = {};
};

#endif