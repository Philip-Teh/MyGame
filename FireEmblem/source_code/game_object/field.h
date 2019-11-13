#ifndef FIELD_H_
#define FIELD_H_

class CField : public CGameObject {
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11Buffer* m_IndexBuffer = NULL;
	CTexture* m_Texture = NULL;
public:
	void Init(/*float sizex, float sizez, int numx, int numz*/);
	void Uninit();
	void Update();
	void Draw();
};

#endif