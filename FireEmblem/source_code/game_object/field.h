#ifndef FIELD_H_
#define FIELD_H_

class CField : public CGameObject {
public:
	void Init(std::string texture);
	void Uninit();
	void Update();
	void Draw(XMFLOAT3 position);

private:
	ID3D11Buffer* mpVertexBuffer = nullptr;
	ID3D11Buffer* mpIndexBuffer = nullptr;
	CTexture* mpTexture = nullptr;

	int NumVertices = NULL;
	float sizex = 10, sizez = 10;
	int numx = 1, numz = 1;
};

#endif