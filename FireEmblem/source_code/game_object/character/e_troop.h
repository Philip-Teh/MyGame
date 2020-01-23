#pragma once

//============================================================================
//=																			 =
//=							キャラクター　敵の兵士							 =
//=																			 =
//============================================================================

#ifndef ETROOP_H_
#define ETROOP_H_

class CEnemyTroop : public CEnemy
{
public:
	CEnemyTroop();
	~CEnemyTroop();

	void Update();
	void Draw(XMFLOAT3 position);

	void Move(CObjectType** type, CBoxType** box, XMFLOAT3 Pposition);
	bool Hit(CBoxType** box);

	bool GetEnable() { return mEnable; }

	XMFLOAT3 GetPosition() { return m_Position; }
	void SetPosition(XMFLOAT3 position) { m_Position = position; }

private:
	const char* mFile[3];
	std::unique_ptr<CModelAnimation> mpModel;
	unsigned int mFrame = 0;
	bool mMove = false;
	bool mEnable = false;
	CDirection mDirection;

	CDirection random()
	{
		int rand = std::rand();

		if (rand >= 0 && rand <= 8191)
			return CDirection::Down;

		else if (rand >= 8192 && rand <= 16383)
			return CDirection::Up;

		else if (rand >= 18384 && rand <= 24575)
			return CDirection::Right;

		else if (rand >= 24576 && rand <= RAND_MAX)
			return CDirection::Left;

		else
			return CDirection::Down;
	}

	void Patrol(XMINT2 position, CObjectType** type, CBoxType** box, XMFLOAT3 Pposition);
	CDirection Tracking(XMFLOAT3 posiiton);
	CDirection DirectionConform(XMFLOAT3 position,int i,XMFLOAT2 front);
	void Animation();
};

#endif // !ETROOP_H_
