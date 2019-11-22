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
	void Init(void);
	void Uninit(void);
	void Draw(void);

	void Create(XMFLOAT3 position);

private:
	CTexture* mpTexture = nullptr;

	ID3D11Buffer* mpVertexBuffer = nullptr;
	ID3D11Buffer* mpIndexBuffer = nullptr;

	CCamera* mpCamera = nullptr;
};



#endif // BILLBOARD_H_
