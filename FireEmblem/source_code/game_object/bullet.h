#pragma once

//============================================================================
//=																			 =
//=						�v���[���[�����e�N���X							 =
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
	CModel* model;
	Collision* collision;
	bool enable;
};

#endif