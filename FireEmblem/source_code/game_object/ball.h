#pragma once
#ifndef BALL_H_
#define BALL_H_

class CBall : public CGameObject
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	XMFLOAT3 GetPosition();

private:
	CModel* model = nullptr;
	XMVECTOR mQuaternion;
	const char* file[3];
	int mFrame;
};

#endif // !BALL_H_
