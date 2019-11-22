#pragma once

//============================================================================
//=																			 =
//=							ゲームオブジェクト　木							 =
//=																			 =
//============================================================================

#ifndef FOREST_H_
#define FOREST_H_

class CForest : public CGameObject
{
public:
	CForest();
	~CForest();

	void Update();
	void Draw(XMFLOAT3 position);

private:
	std::unique_ptr<CField> mpField;
	std::string mTexture = "";
};

#endif // !FOREST_H_

