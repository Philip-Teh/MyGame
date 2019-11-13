#ifndef POLYGON_H_
#define POLYGON_H_

#define TEXTURE (10)

class CPolygon : public CGameObject{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	CTexture* m_Texture = NULL;
	bool enable = false;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Create(std::string texture,XMFLOAT3 position, float sizeX, float sizeY);
};

#endif