#ifndef FIELD_H_
#define FIELD_H_

class CField : public CGameObject {
public:
	void Init(std::string texture);
	void Init(std::string texture, float x, float z,XMFLOAT3 rgb);
	void Uninit();
	void Update();
	void Draw(XMFLOAT3 position, float rotate);

private:
	ID3D11Buffer* mpVertexBuffer = nullptr;
	ID3D11Buffer* mpIndexBuffer = nullptr;
	CTexture* mpTexture = nullptr;

	int NumVertices = NULL;
	float sizex = 1.0f, sizez = 1.0f;
	int numx = 1, numz = 1;
};

#endif