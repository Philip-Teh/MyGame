#ifndef CAMERA_H_
#define CAMERA_H_

class CCamera : public CGameObject
{
private:
	RECT m_Viewport;
	XMMATRIX m_ViewMatrix = XMMatrixIdentity();
	XMMATRIX m_ProjectionMatrix = XMMatrixIdentity();
	
	XMFLOAT3 front, up, right;
	XMVECTOR vectorF = XMVectorZero(), vectorR = XMVectorZero(), vectorU = XMVectorZero();
	XMVECTOR eye = XMVectorZero(), focus = XMVectorZero();
	float mLength = 0;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Set(XMFLOAT3 position) { m_Position = position; }

	XMMATRIX GetViewMatrix(void) { return m_ViewMatrix; }
	bool Getvisivility(XMFLOAT3 Position);
};

#endif