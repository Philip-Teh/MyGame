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
	CPlain();
	~CPlain();

	void Update();
	void Draw(XMFLOAT3 position);

private:
	std::unique_ptr<CField> mpField;
	std::string mTexture = "";
};

#endif // !PLAIN_H_
