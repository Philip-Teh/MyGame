#pragma once

//============================================================================
//=																			 =
//=							ゲームオブジェクト	壁							 =
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
	std::shared_ptr<CShader> mpShader = nullptr;

	const char* mFile = "";
};

#endif // !MOUNTAIN_H_

