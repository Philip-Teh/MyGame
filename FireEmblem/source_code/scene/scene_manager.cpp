

CScene* CSceneManager::m_Scene = nullptr;

void CSceneManager::Init()
{
	CRenderer::Init();
	CInput::Init();
	CAudioClip::Init();

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