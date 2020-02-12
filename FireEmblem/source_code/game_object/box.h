#pragma once

//============================================================================
//=																			 =
//=							ゲームオブジェクト　箱							 =
//=																			 =
//============================================================================

#ifndef BOX_H_
#define BOX_H_

class CBox : public CGameObject
{
public:
	CBox();
	~CBox();

	void Update();
	void Draw(XMFLOAT3 position,int num);

private:
	std::unique_ptr<CModelAnimation> mpModel[2] = {};
	CShader* mpShader = nullptr;

	const char* mFile[3] = {};
	const char* mFile1[3] = {};
};

#endif // !FOREST_H_

