#pragma once

#ifndef CAMERA_H_
#define CAMERA_H_

class CCamera : public CGameObject
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetPosition(XMFLOAT3 position) { m_Position = position; }
	XMFLOAT3 GetPosition() { return m_Position; }

	XMMATRIX GetViewMatrix(void) { return m_ViewMatrix; }
	XMMATRIX GetProjectionMatrix() { return m_ProjectionMatrix; }

	bool Getvisivility(XMFLOAT3 Position);

	void SetCenter(XMFLOAT3 pos) { mCenter = pos; }

private:
	RECT m_Viewport;
	XMMATRIX m_ViewMatrix = XMMatrixIdentity();
	XMMATRIX m_ProjectionMatrix = XMMatrixIdentity();
	
	XMFLOAT3 front, up, right;
	XMVECTOR vectorF = XMVectorZero(), vectorR = XMVectorZero(), vectorU = XMVectorZero();
	XMVECTOR eye = XMVectorZero(), focus = XMVectorZero();
	XMFLOAT3 mCenter = XMFLOAT3(0.0f, 0.0f, 0.0f);
	float mLength = 0;
};

#endif