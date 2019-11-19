#pragma once

//============================================================================
//=																			 =
//=								íäè€ÉNÉâÉXÅ@ìG								 =
//=																			 =
//============================================================================

#ifndef ENEMY_H_
#define ENEMY_H_

class CEnemy
{
public:
	virtual~CEnemy() = default;

	virtual void Init() {}
	virtual void Uninit() {}
	virtual void Update() {}
	virtual void Draw(XMFLOAT3 position) {}

protected:
	XMFLOAT3 m_Position = XMFLOAT3(0.0f, .0f, 0.0f);
	XMFLOAT3 m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

};

#endif // !ENEMY_H_

