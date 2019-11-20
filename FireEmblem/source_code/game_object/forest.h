#pragma once

//============================================================================
//=																			 =
//=							�Q�[���I�u�W�F�N�g�@��							 =
//=																			 =
//============================================================================

#ifndef FOREST_H_
#define FOREST_H_

class CForest : public CGameObject
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw(XMFLOAT3 position);

private:
	std::unique_ptr<CField> mpField;
	const char* mTexture = nullptr;
};

#endif // !FOREST_H_

