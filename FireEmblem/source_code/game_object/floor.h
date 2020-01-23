#pragma once

//============================================================================
//=																			 =
//=							 �Q�[���I�u�W�F�N�g�@��							 =
//=																			 =
//============================================================================

#ifndef FLOOR_H_
#define FLOOR_H_

class CFloor : public CGameObject
{
public:
	CFloor();
	~CFloor();

	void Update();
	void Draw(XMFLOAT3 position);

private:
	std::unique_ptr<CField> mpField;
	std::string mTexture = "";
};

#endif // !FLOOR_H_
