

CScene* CSceneManager::m_Scene = nullptr;

void CSceneManager::Init()
{
	CRenderer::Init();
	CInput::Init();
	CAudioClip::Init();

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

	CAudioClip::Uninit();
	CInput::Uninit();
	CRenderer::Uninit();
}

void CSceneManager::Update()
{
	CInput::Update();

	m_Scene->Update();
}

void CSceneManager::Draw()
{
	CRenderer::Begin();

	m_Scene->Draw();

	CRenderer::End();
}

CScene* CSceneManager::GetScene()
{
	return m_Scene;
}