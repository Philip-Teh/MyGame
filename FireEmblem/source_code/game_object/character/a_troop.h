#pragma once

//============================================================================
//=																			 =
//=								�����̕��m									 =
//=																			 =
//============================================================================

#ifndef ATROOP_H_
#define ATROOP_H_

class CAlliesTroop : public CAllies
{
public:
	CAlliesTroop();
	~CAlliesTroop();

	void Update();
	void Draw(XMFLOAT3 position);

private:
	std::string mTexture = "";
	std::unique_ptr<CField> mpField;
};

#endif // !ATROOP_H_
