#pragma once

//============================================================================
//=																			 =
//=						プレーヤーが撃つ弾クラス							 =
//=																			 =
//============================================================================

#ifndef BULLET_H_
#define BULLET_H_


class CBullet : public CGameObject
{
public:
	~CBullet() = default;

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Create(XMFLOAT3 position);

private:
	CModel* mpModel = nullptr;
	Collision* mpCollision = nullptr;
	bool mEnable = false;
};

#endif
