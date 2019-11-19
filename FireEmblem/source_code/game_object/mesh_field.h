#ifndef MESHFIELD_H_
#define MESHFIELD_H_

class CMeshfield : public CGameObject {
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	float GetHeight(XMFLOAT3 position);

private:
	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11Buffer* m_IndexBuffer = nullptr;

	VERTEX_3D* Vertex = nullptr;
	unsigned short* Index = nullptr;
	unsigned short NumVertex = NULL;
	unsigned short NumIndex = NULL;

	float sizex = NULL, sizez = NULL;
	int numx = NULL, numz = NULL;

	CTexture* m_Texture = nullptr;
};

#endif
