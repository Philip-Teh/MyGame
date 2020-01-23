#pragma once

//============================================================================
//=																			 =
//=						キャラクター　プレイヤー							 =
//=																			 =
//============================================================================

#ifndef PLAYER_H_
#define PLAYER_H_

class CPlayer : public CGameObject
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw(XMFLOAT3 position);

	CDirection GetDirection() { return mDirection; }
	void SetDirection(CDirection direction) { mDirection = direction; }

	XMFLOAT3 GetPosition() { return m_Position; }
	void SetPosition(XMFLOAT3 position) { m_Position = position; }

	bool GetMove() { return mMove; }

	int GetStep() { return mStep; }
	void SetStep(int step) { mStep = step; }
	void CaculateStep(int step) { mStep += step; }

private:
	const char* mAnimation[3] = {};
	CModelAnimation* mpModelA = nullptr;
	unsigned int mFrame = NULL;

	int mStep = 0;
	bool mMove = false;
	CDirection mDirection = CDirection::Down;

	void Move();
	void Direction();
};

#endif
