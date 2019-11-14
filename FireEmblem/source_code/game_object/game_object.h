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
	virtual~CGameObject() = default;

	virtual void Init(){}
	virtual void Uninit(){}
	virtual void Update(){}
	virtual void Draw(XMFLOAT3 position){}

	bool m_Destroy = false;

	void SetDestroy(void) { m_Destroy = true; }
	bool Destroy() { if (m_Destroy) { Uninit(); delete this; return true; } else { return false; } }

protected:
	XMFLOAT3 m_Position = XMFLOAT3(0.0f,.0f,0.0f);
	XMFLOAT3 m_Rotation = XMFLOAT3(0.0f,0.0f,0.0f);
	XMFLOAT3 m_Scale    = XMFLOAT3(1.0f,1.0f,1.0f);

};

#endif 

