#ifndef PLAYER_H_
#define PLAYER_H_

class CModel;
class ModelA;

class CPlayer : public CGameObject
{
private:
	CModel* model = nullptr;
	//ModelA* modela = nullptr;
	int mFrame;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	XMFLOAT3 GetPosition();
};

#endif
