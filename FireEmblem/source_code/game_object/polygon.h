#ifndef POLYGON_H_
#define POLYGON_H_

#define TEXTURE (10)

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
	ID3D11Buffer* m_VertexBuffer = nullptr;
	CTexture* mTexture = nullptr;
	bool enable = false;
	XMFLOAT2 size = XMFLOAT2(0.0f, 0.0f);
};

#endif