#pragma once

//============================================================================
//=																			 =
//=							�L�����N�^�[�@�G�̕��m							 =
//=																			 =
//============================================================================

#ifndef ETROOP_H_
#define ETROOP_H_

class CEnemyState;

class CEnemyTroop : public CEnemy
{
public:
	CEnemyTroop();
	~CEnemyTroop();

	void Update(CObjectType** type, CBoxType** box, XMFLOAT3 playerposition);
	void Draw(XMFLOAT3 position);
	void Action();
	void ChangeState(CEnemyState* p);
	bool Hit(CBoxType** box, CDirection playerdirection);

	const bool& GetCollisionEnable() { return mCollisionEnable; }
	const XMFLOAT2& GetMoveOffset() { return mMoveOffset; }

	XMFLOAT3 GetPosition() { return m_Position; }
	void SetPosition(XMFLOAT3 position) { m_Position = position; }

private:
	const char* mFile[3] = {};
	std::unique_ptr<CModelAnimation> mpModel;
	CShader* mpShader;

	const float mTurnSpeed = 0.1f;
	const int mMoveSpeed = 30;
	const float mDownSpeed = 0.05f;
	const float mDown = 1.5f;
	const int mMap = 17;
	const int mRange = 5;
	const int mMoveDuration = 30;

	struct MovableDirection
	{
		CDirection direction;
		bool enable;
	};
	MovableDirection mMovaD[4];

	bool mMoving = false;
	bool mComplete = true;
	int mMoveCount = 0;
	XMINT2 mMoveDirection = XMINT2(0, 0);
	XMFLOAT2 mMoveOffset = XMFLOAT2(0.0f, 0.0f);

	unsigned int mFrame = 0;
	bool mMove = false;
	bool mEnable = false;
	bool mCollisionEnable = false;
	bool mActionChange = false;
	bool mHitting = false;

	CDirection mPlayerDirect1;
	CDirection mPlayerDirect2;

	CObjectType** mpType;
	CBoxType** mpBox;

	CDirection mDirection;
	CDirection mCurrentDirection;
	CRotation mCurrentRotation;
	CEnemyState* mpState;
	CAction mAction;

	void Move(CObjectType** type, CBoxType** box, XMINT2 playerposition);
	void Patrol(XMINT2 position, CObjectType** type, CBoxType** box, XMINT2 playerposition);
	bool MoveAnimation();
	CDirection Chase(XMINT2 playerposition, CObjectType** type, CBoxType** box);

	bool Collision(XMINT2 position, CObjectType** type, CBoxType** box);

	bool DownDirection(CDirection playerdirection);
	bool Falling(bool rotation, bool minus);
	void Direction();

	CDirection RandomDirection2(CDirection direction1,CDirection direction2)
	{
		int rand = std::rand();

		if (rand >= 0 && rand <= 16383)
			return direction1;

		else if (rand >= 16384 && rand <= RAND_MAX)
			return direction2;
	}

	CDirection RandomDirection3(CDirection direction1, CDirection direction2, CDirection direction3)
	{
		int rand = std::rand();

		if (rand >= 0 && rand <= 10922)
			return direction1;

		else if (rand >= 10923 && rand <= 21844)
			return direction2;

		else if (rand >= 21845 && rand <= RAND_MAX)
			return direction3;
	}

	CDirection RandomDirection4()
	{
		int rand = std::rand();

		if (rand >= 0 && rand <= 8191)
			return CDirection::Up;

		else if (rand >= 8192 && rand <= 16383)
			return CDirection::Down;

		else if (rand >= 16384 && rand <= 24575)
			return CDirection::Left;

		else if (rand >= 24576 && rand <= RAND_MAX)
			return CDirection::Right;
	}
};

#endif // !ETROOP_H_