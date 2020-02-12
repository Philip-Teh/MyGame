#pragma once

//============================================================================
//=																			 =
//=						�Q�[���I�u�W�F�N�g	�o��Ȃ��R						 =
//=																			 =
//============================================================================

#ifndef WALL_H_
#define WALL_H_

class CWall : public CGameObject
{
public:
	CWall();
	~CWall();

	void Update();
	void Draw(XMFLOAT3 position);

private:
	std::unique_ptr<CModelAnimation> mpModel = nullptr;
	CShader* mpShader = nullptr;

	const char* mFile[3] = {};
};

#endif // !MOUNTAIN_H_

