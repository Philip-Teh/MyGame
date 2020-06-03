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
	const char* mFile[3] = {};
	std::unique_ptr<CModelAnimation> mpModel[3] = {};
	std::shared_ptr<CShader> mpShader = nullptr;

};

#endif // !FOREST_H_

