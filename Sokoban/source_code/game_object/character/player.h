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

	//移動中のアニメーション
	void MoveAnimation(bool move);

	const CDirection& GetDirection() { return mDirection; }
	void SetDirection(CDirection direction) { mDirection = direction; }

	const XMFLOAT3& GetPosition() { return m_Position; }
	void SetPosition(XMFLOAT3 position) { m_Position = position; }

	const bool& GetMove() { return mMove; }
	const bool& GetPull() { return mPull; }
	void SetPullEnable(bool enable) { mPullEnable = enable; }

	const int& GetStep() { return mStep; }
	void SetStep(int step) { mStep = step; }

	//ステップの計算
	void CaculateStep(int step) { mStep += step; }

private:
	const char* mAnimation[3] = {};
	std::unique_ptr<CModelAnimation> mpModelA = nullptr;
	std::shared_ptr<CShader> mpShader = nullptr;

	unsigned int mFrame = 0;
	const float mTurnSpeed = 0.15f;

	int mStep = 0;
	bool mMove = false;
	bool mPull = false;
	bool mPullEnable = false;
	CDirection mDirection = CDirection::Down;
	CDirection mCurrentDirection = CDirection::Down;
	CRotation mCurrentRotation;

	//キー入力で移動処理
	void Move();

	//方向回転のアニメーション
	void Direction();
};

#endif
