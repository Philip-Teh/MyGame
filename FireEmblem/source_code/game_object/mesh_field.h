#ifndef MESHFIELD_H_
#define MESHFIELD_H_

class CMeshfield : public CGameObject {
private:
	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11Buffer* m_IndexBuffer = nullptr;

	VERTEX_3D* Vertex=nullptr;
	unsigned short* Index=nullptr;
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

	float GetHeight(XMFLOAT3 position);
};

#endif
