#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

//============================================================================
//=																			 =
//=					インターフェース	ゲームオブジェクト　				 =
//=																			 =
//============================================================================

class CGameObject 
{
public:
	virtual~CGameObject() {}

	virtual void Init(){}
	virtual void Uninit(){}
	virtual void Update(){}
	virtual void Draw(){}

	bool m_Destroy = false;

	void SetDestroy(void) { m_Destroy = true; }
	bool Destroy() { if (m_Destroy) { Uninit(); delete this; return true; } else { return false; } }

protected:
	XMFLOAT3 m_Position = XMFLOAT3(0.0f,.0f,0.0f);
	XMFLOAT3 m_Rotation = XMFLOAT3(0.0f,0.0f,0.0f);
	XMFLOAT3 m_Scale    = XMFLOAT3(0.0f,0.0f,0.0f);

};

#endif 

