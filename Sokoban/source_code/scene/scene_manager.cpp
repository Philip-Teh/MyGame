

CScene* CSceneManager::m_Scene = nullptr;

void CSceneManager::Init()
{
	//静的クラス初期化
	CRenderer::Init();
	CInput::Init();
	CAudioClip::Init();
	CLoading::Init();
	CEnter::Init();

	//音声をロード
	CAudioClip::Load("asset/BGM/start.wav");
	CAudioClip::Load("asset/BGM/game.wav");
	CAudioClip::Load("asset/BGM/clear.wav");
	CAudioClip::Load("asset/BGM/end.wav");

	//最初のシーンを設定
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

	//ローディング開始時、更新処理
	if (CLoading::GetEnable())
		//ローディング終了時、無効にする
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