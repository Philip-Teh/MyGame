#pragma once

//============================================================================
//=																			 =
//=								���ۃN���X�@�V�[��							 =
//=																			 =
//============================================================================

#ifndef SCENE_H_
#define SCENE_H_

//enum GAMEOBJ
//{
//	FIRST,
//	WORLD,
//	CHARACTER,
//	UI,
//
//	MAXGAMEOBJ
//};

class CScene {
protected:
	std::list<CGameObject*> m_GameObject;

public:
	CScene(){}
	virtual ~CScene(){}

	virtual void Init() = 0;
	void DestroyGameObject(CGameObject* gameObject) { gameObject->SetDestroy(); }

	template <typename T>
	T* AddGameObject()
	{
		T* object = new T();
		object->Init();
		m_GameObject.push_back(object);
		return object;
	}

	//��̃I�u�W�F�N�g�擾
	template<typename T>
	T* GetGameObject()
	{
		for (CGameObject* object : m_GameObject)
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
	std::vector<T*>GetGameObjects()
	{
		std::vector<T*>objects;

		for (CGameObject* object : m_GameObject)
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
			for (CGameObject* object : m_GameObject)
			{
				object->Uninit();
				delete object;
			}
			//List���N���A���邽�ߕK���ĂԂ���
			m_GameObject.clear();
		
	}

	virtual void Update()
	{
		
			for (CGameObject*object : m_GameObject)
			{
				object->Update();
			}
			m_GameObject.remove_if([](CGameObject* object)
				{ return object->Destroy(); }
			);
		
	}

	virtual void Draw0()
	{
			for (CGameObject*object : m_GameObject)
			{
				object->Draw();
			}
	}

	virtual void Draw() = 0;
};

#endif 

