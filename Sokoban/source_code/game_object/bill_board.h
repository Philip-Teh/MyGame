#pragma once

//============================================================================
//=																			 =
//=						ゲームオブジェクト　ビルボード						 =
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

	ID3D11Buffer* mpVertexBuffer = nullptr;	//頂点バッファ
	ID3D11Buffer* mpIndexBuffer = nullptr;	//インデックスバッファ

	CCamera* mpCamera = nullptr;
};



#endif // BILLBOARD_H_
