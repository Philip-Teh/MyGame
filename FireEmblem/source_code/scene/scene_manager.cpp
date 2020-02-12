

CScene* CSceneManager::m_Scene = nullptr;

void CSceneManager::Init()
{
	CRenderer::Init();
	CInput::Init();
	CAudioClip::Init();
	CLoading::Init();

	CGameStatus::SetGameClear(false);
	CGameStatus::SetGameOver(false);
	CGameStatus::SetScore(0);
	CGameStatus::SetStageClear(0);
	CGameStatus::SetStageChoose(1);

	SetScene<CTitle>();
}

void CSceneManager::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;

	CLoading::Uninit();
	CAudioClip::Uninit();
	CInput::Uninit();
	CRenderer::Uninit();
}

void CSceneManager::Update()
{
	CInput::Update();

	m_Scene->Update();

	if (CLoading::GetEnable())
		if (CLoading::Update())
			CLoading::SetEnable(false);
}

void CSceneManager::Draw()
{
	CRenderer::Begin();

	m_Scene->Draw0();
	m_Scene->Draw();

	CLoading::Draw();

	CRenderer::End();
}

CScene* CSceneManager::GetScene()
{
	return m_Scene;
}