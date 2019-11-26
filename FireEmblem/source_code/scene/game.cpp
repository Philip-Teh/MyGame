
void CGame::Init()
{
	mTexture = "asset/aim.png";

	AddGameObject<CCamera>(FIRST);
	AddGameObject<CSkydome>(WORLD);
	//AddGameObject<CMeshfield>(WORLD);
	//AddGameObject<CField>(WORLD);
	//AddGameObject<CBall>(CHARACTER);
	//AddGameObject<CBillBoard>(WORLD);
	//AddGameObject<CPlayer>(CHARACTER);
	AddGameObject<CBEnemy>(CHARACTER)->Create(XMFLOAT3(-5.0f, 3.0f, 5.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f));
	AddGameObject<CBEnemy>(CHARACTER)->Create(XMFLOAT3(0.0f, 2.0f, 5.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f));
	AddGameObject<CBEnemy>(CHARACTER)->Create(XMFLOAT3(5.0f, 1.0f, 5.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f));
	AddGameObject<CStageManager>(UI);
	AddGameObject<CPolygon>(UI)->Create(mTexture, XMFLOAT3(SCREEN_WIDTH*0.45f, SCREEN_HEIGHT*0.4f, 0.0f), 100, 100);

	m_BGM = new CAudioClip();
	m_BGM->Load("asset/game.wav");
	m_BGM->Play(false);
}

void CGame::Uninit()
{
	m_BGM->Stop();
	m_BGM->Unload();
	delete m_BGM;

	CScene::Uninit();
}

void CGame::Update()
{
	CScene::Update();

	if (CInput::GetKeyTrigger(VK_RETURN))
	{
		if (!GetGameObject<CBEnemy>(CHARACTER))
			CSceneManager::SetScene<CResult>();
	}
}