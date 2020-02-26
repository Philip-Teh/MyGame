#pragma once

//============================================================================
//=																			 =
//=							ゲームオブジェクト　ゴール						 =
//=																			 =
//============================================================================

#ifndef GOAL_H_
#define GOAL_H_

class CGoal : public CGameObject
{
public:
	CGoal();
	~CGoal();

	void Update();
	void Draw(XMFLOAT3 position, bool trigger);

	XMFLOAT3 GetPosition() { return m_Position; }
	void SetPosition(XMFLOAT3 position) { m_Position = position; }

private:
	std::unique_ptr<CModelAnimation> mpModel = nullptr;
	std::unique_ptr<CModelAnimation> mpAnimation = nullptr;
	CShader* mpShader = nullptr;

	const float mRotateSpeed = 0.03f;

	const char* mFile[3] = {};
	const char* mAnimation[3] = {};

	unsigned int mFrame = 0;
	float mRotate = 0.0f;
};

#endif // !ATROOP_H_
