

CScene* CSceneManager::m_Scene = nullptr;

void CSceneManager::Init()
{
	CRenderer::Init();
	CInput::Init();
	CAudioClip::Init();
	CLoading::Init();
	CEnter::Init();

	SetScene<CTitle>();
}

void CSceneManager::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;

	CEnter::Uninit();
	CLoading::Uninit();
	CAudioClip::Uninit();
	CInput::Uninit();
	CRenderer::Uninit();
}

void CSceneManager::Update()
{
	CInput::Update();

	m_Scene->Update();
	CEnter::Update();

	if (CLoading::GetEnable())
		if (CLoading::Update())
			CLoading::SetEnable(false);
}

void CSceneManager::Draw()
{
	CRenderer::Begin();

	m_Scene->Draw0();
	m_Scene->Draw();
	CEnter::Draw();

	CLoading::Draw();

	CRenderer::End();
}

CScene* CSceneManager::GetScene()
{
	return m_Scene;
}