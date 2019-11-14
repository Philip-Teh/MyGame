#ifndef CAMERA_H_
#define CAMERA_H_

class CCamera : public CGameObject
{
private:
	RECT m_Viewport;
	XMMATRIX m_ViewMatrix, m_ProjectionMatrix;
	
	XMFLOAT3 front, up, right;
	XMVECTOR vectorF, vectorR, vectorU;
	XMVECTOR eye, focus;
	CPlayer player;
	XMFLOAT3 pp;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	XMMATRIX GetViewMatrix(void) { return m_ViewMatrix; }
	bool Getvisivility(XMFLOAT3 Position);
};

#endif