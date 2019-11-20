#pragma once

//============================================================================
//=																			 =
//=						ゲームオブジェクト	登れない山						 =
//=																			 =
//============================================================================

#ifndef MOUNTAIN_H_
#define MOUNTAIN_H_

class CMountain : public CGameObject
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

#endif // !MOUNTAIN_H_

