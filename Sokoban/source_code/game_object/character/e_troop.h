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

	//�G�̍s��
	void Action();

	//�G�̍s����ς���
	void ChangeState(CEnemyState* p);

	//���ƓG�̓����蔻��
	bool Hit(CBoxType** box, CDirection playerdirection, XMINT2 map);

	const bool& GetCollisionEnable() { return mCollisionEnable; }
	const XMFLOAT2& GetMoveOffset() { return mMoveOffset; }

	XMFLOAT3 GetPosition() { return m_Position; }
	void SetPosition(XMFLOAT3 position) { m_Position = position; }

private:
	const char* mFile[3] = {};
	std::string mTexture = "";

	std::unique_ptr<CModelAnimation> mpModel = nullptr;
	std::unique_ptr<CEffect> mpEffect = nullptr;
	std::shared_ptr<CShader> mpShader = nullptr;
	std::unique_ptr<CBillBoard> mpBillboard = nullptr;

	const float mTurnSpeed = 0.1f;
	const unsigned int mMoveSpeed = 30;
	const float mDownSpeed = 0.05f;		//�|���X�s�[�h
	const float mDown = 1.5f;			//���p�x
	const int mMoveDuration = 30;

	struct MovableDirection
	{
		CDirection direction;
		bool enable;
	};
	//�ړ��ł������
	MovableDirection mMovaD[4] = {};

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

	CDirection mDirection;
	CDirection mCurrentDirection;
	CRotation mCurrentRotation;
	CEnemyState* mpState;
	CAction mAction;

	void Move(CObjectType** type, CBoxType** box, XMINT2 playerposition);

	//�ړ��\�ȕ�����T��
	void Patrol(XMINT2 position, CObjectType** type, CBoxType** box, XMINT2 playerposition);
	bool MoveAnimation();

	//�v���C���[��ǂ�������
	CDirection Chase(XMINT2 playerposition, CObjectType** type, CBoxType** box);

	//�����蔻��
	bool Collision(XMINT2 position, CObjectType** type, CBoxType** box);

	//�|������
	bool DownDirection(CDirection playerdirection);

	//�|��鎞�̓���
	bool Falling(bool rotation, bool minus);
	void Direction();

	//��̕����𗐐��ŕԂ�
	CDirection RandomDirection2(CDirection direction1,CDirection direction2)
	{
		int rand = std::rand();

		if (rand >= 0 && rand <= 16383)
			return direction1;

		else if (rand >= 16384 && rand <= RAND_MAX)
			return direction2;

		else return CDirection::None;
	}

	//�O�̕����𗐐��ŕԂ�
	CDirection RandomDirection3(CDirection direction1, CDirection direction2, CDirection direction3)
	{
		int rand = std::rand();

		if (rand >= 0 && rand <= 10922)
			return direction1;

		else if (rand >= 10923 && rand <= 21844)
			return direction2;

		else if (rand >= 21845 && rand <= RAND_MAX)
			return direction3;

		else return CDirection::None;
	}

	//�l�̕����𗐐��ŕԂ�
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

		else return CDirection::None;
	}
};

#endif // !ETROOP_H_
