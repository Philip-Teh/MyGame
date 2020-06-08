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

public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
	static CScene* GetScene();

	//今のシーンを終了して、次のシーンの初期化
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
private:
	static CScene* m_Scene;

};

#endif