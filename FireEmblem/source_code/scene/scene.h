#ifndef SCENE_H_
#define SCENE_H_

#include <list>

enum GAMEOBJ
{
	FIRST,
	WORLD,
	CHARACTER,
	UI,

	MAXGAMEOBJ
};

class CScene {
protected:
	std::list<CGameObject*> m_GameObject[5];

public:
	CScene(){}
	virtual ~CScene(){}

	virtual void Init() = 0;
	void DestroyGameObject(CGameObject* gameObject) { gameObject->SetDestroy(); }

	template <typename T>
	T* AddGameObject(int layer)
	{
		T* object = new T();
		object->Init();
		m_GameObject[layer].push_back(object);
		return object;
	}

	//��̃I�u�W�F�N�g�擾
	template<typename T>
	T* GetGameObject(int layer)
	{
		for (CGameObject* object : m_GameObject[layer])
		{
			if (typeid(*object) == typeid(T))
			{
				return(T*)object;
			}
		}
		return nullptr;
	}

	//�����̃I�u�W�F�N�g�擾
	template<typename T>
	std::vector<T*>GetGameObjects(int layer)
	{
		std::vector<T*>objects;

		for (CGameObject* object : m_GameObject[layer])
		{
			if (typeid(*object) == typeid(T))
			{
				objects.push_back((T*)object);
			}
		}
		return objects;
	}

	virtual void Uninit()
	{
		for (int i = 0; i < MAXGAMEOBJ; i++)
		{
			for (CGameObject* object : m_GameObject[i])
			{
				object->Uninit();
				delete object;
			}
			//List���N���A���邽�ߕK���ĂԂ���
			m_GameObject[i].clear();
		}
	}

	virtual void Update()
	{
		for (int i = 0; i < MAXGAMEOBJ; i++)
		{
			for (CGameObject *object : m_GameObject[i])
			{
				object->Update();
			}
			m_GameObject[i].remove_if([](CGameObject* object)
				{ return object->Destroy(); }
			);
		}
	}

	virtual void Draw()
	{
		for (int i = 0; i < MAXGAMEOBJ; i++)
		{
			for (CGameObject *object : m_GameObject[i])
			{
				object->Draw();
			}
		}
	}
};

#endif 

