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
	void Draw();

	XMFLOAT3 GetPosition() { return m_Position; }

private:
	const char* mAnimation[3] = {};
	CModelAnimation* mpModelA = nullptr;
	int mFrame = NULL;
};

#endif
