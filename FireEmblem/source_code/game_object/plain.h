#pragma once

//============================================================================
//=																			 =
//=									 Plain									 =
//=																			 =
//============================================================================

#ifndef PLAIN_H_
#define PLAIN_H_

class CPlain : public CGameObject
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

#endif // !PLAIN_H_
