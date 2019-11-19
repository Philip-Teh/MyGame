#pragma once

//============================================================================
//=																			 =
//=							シーン　マネージャー							 =
//=																			 =
//============================================================================

#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

class CSceneManager
{
private:
	static CScene* m_Scene;

public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
	static CScene* GetScene();

	template <typename T>
	static void SetScene()
	{
		if (m_Scene != nullptr)
		{
			m_Scene->Uninit();
			delete m_Scene;
		}
		m_Scene = new T();
		m_Scene->Init();
	}
};

#endif