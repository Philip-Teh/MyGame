#ifndef BILLBOARD_H_
#define BILLBOARD_H_

class BillBoard : public CGameObject
{
private:
	CTexture* g_texture;

	ID3D11Buffer* VertexBuffer = nullptr;
	ID3D11Buffer* IndexBuffer = nullptr;

public:
	void Init(void);
	void Uninit(void);
	void Draw(void);

	void Create(XMFLOAT3 position);
};



#endif // BILLBOARD_H_
