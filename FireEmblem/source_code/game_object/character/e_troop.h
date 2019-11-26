#pragma once

//============================================================================
//=																			 =
//=							キャラクター　敵の兵士							 =
//=																			 =
//============================================================================

#ifndef ETROOP_H_
#define ETROOP_H_

class CEnemyTroop : public CEnemy
{
public:
	CEnemyTroop();
	~CEnemyTroop();

	void Update();
	void Draw(XMFLOAT3 position);

private:
	std::string mTexture = "";
	std::unique_ptr<CField> mpField;
};

#endif // !ETROOP_H_
