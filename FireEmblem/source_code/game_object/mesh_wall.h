#ifndef MESHWALL_H_
#define MESHWALL_H_

class CMeshwall : public CGameObject {
private:
	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11Buffer* m_IndexBuffer = nullptr;

	VERTEX_3D* Vertex = nullptr;
	unsigned short* Index = nullptr;
	unsigned short NumVertex = 0;
	unsigned short NumIndex = 0;

	float sizex, sizez;
	int numx, numz;

	CTexture* m_Texture = nullptr;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Set(XMFLOAT3 position,XMFLOAT3 rotation);
};

#endif
