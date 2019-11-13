#ifndef CAMERA_H_
#define CAMERA_H_

class CCamera : public CGameObject
{
private:
	RECT m_Viewport;
	XMMATRIX m_ViewMatrix;
	
	XMFLOAT3 front, up, right;
	XMVECTOR vectorF, vectorR, vectorU;
	XMVECTOR eye, focus;
	CPlayer player;
	XMFLOAT3 pp;

public:
	XMMATRIX GetViewMatrix(void) { return m_ViewMatrix; }

	void Init();
	void Uninit();
	void Update();
	void Draw();
};

#endif