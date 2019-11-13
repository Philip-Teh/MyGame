#ifndef ENEMY_H_
#define ENEMY_H_


class CEnemy : public CGameObject
{
private:
	CModel* model;
	Collision* collision;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();


	void Create(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scale);
	XMFLOAT3 GetPosition() { return m_Position; }
	Collision* GetCollision() { return collision; }
};

#endif
