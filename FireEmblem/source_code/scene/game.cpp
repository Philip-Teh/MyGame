using namespace std;

void CGame::Init()
{
	//mpCamera = make_unique<CCamera>();
	//mpCamera->Init();
	//mpCamera->Set(XMFLOAT3(3.0f, 5.0f, -7.0f));

	AddGameObject<CCamera>()->Set(XMFLOAT3(3.0f, 5.0f, -7.0f));

	mpSkydome = make_unique<CSkydome>();
	mpSkydome->Init();

	mpMeshField = make_unique<CMeshfield>();
	mpMeshField->Init();

	//AddGameObject<CPolygon>(UI)->Create(mTexture, XMFLOAT3(SCREEN_WIDTH*0.45f, SCREEN_HEIGHT*0.4f, 0.0f), 100, 100);

	mpStageManager = make_unique<CStageManager>();
	mpStageManager->Init();

	m_BGM = new CAudioClip();
	m_BGM->Load("asset/game.wav");
	m_BGM->Play(false);

	CLoading::SetChange(false);
}

void CGame::Uninit()
{
	//mpCamera->Uninit();
	mpSkydome->Uninit();
	mpMeshField->Uninit();
	mpStageManager->Uninit();

	m_BGM->Stop();
	m_BGM->Unload();
	delete m_BGM;

	CScene::Uninit();
}

void CGame::Update()
{
	//mpCamera->Update();
	mpSkydome->Update();
	mpMeshField->Update();
	mpStageManager->Update();

	CScene::Update();

	if (CGameStatus::GetGameClear() && !CGameStatus::GetGameOver())
		CSceneManager::SetScene<CResult>();

	if (CGameStatus::GetGameOver() && !CGameStatus::GetGameClear())
		CSceneManager::SetScene<CGameOver>();
}

void CGame::Draw()
{
	//mpCamera->Draw();
	mpSkydome->Draw();
	mpMeshField->Draw();
	mpStageManager->Draw();
}