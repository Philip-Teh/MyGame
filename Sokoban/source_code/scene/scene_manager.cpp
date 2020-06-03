

CScene* CSceneManager::m_Scene = nullptr;

void CSceneManager::Init()
{
	CRenderer::Init();
	CInput::Init();
	CAudioClip::Init();
	CLoading::Init();
	CEnter::Init();

	CAudioClip::Load("asset/BGM/start.wav");
	CAudioClip::Load("asset/BGM/game.wav");
	CAudioClip::Load("asset/BGM/clear.wav");
	CAudioClip::Load("asset/BGM/end.wav");

	SetScene<CTitle>();
}

void CSceneManager::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;

	CAudioClip::Unload();

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