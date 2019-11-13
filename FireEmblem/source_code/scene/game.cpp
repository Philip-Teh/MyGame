
void CGame::Init()
{
	texture = "asset/aim.png";

	AddGameObject<CCamera>(FIRST);
	AddGameObject<CSkydome>(WORLD);
	AddGameObject<CMeshfield>(WORLD);
	AddGameObject<CMeshwall>(WORLD)->Set(XMFLOAT3(0.0f, 0.0f, 13.0f), XMFLOAT3(-45.0f, 0.0f, 0.0f));
	AddGameObject<CField>(WORLD);
	AddGameObject<CBall>(CHARACTER);
	AddGameObject<CPlayer>(CHARACTER);
	AddGameObject<CEnemy>(CHARACTER)->Create(XMFLOAT3(-5.0f, 3.0f, 5.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f));
	AddGameObject<CEnemy>(CHARACTER)->Create(XMFLOAT3(0.0f, 2.0f, 5.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f));
	AddGameObject<CEnemy>(CHARACTER)->Create(XMFLOAT3(5.0f, 1.0f, 5.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f));
	AddGameObject<CPolygon>(UI)->Create(texture, XMFLOAT3(SCREEN_WIDTH*0.45f, SCREEN_HEIGHT*0.4f, 0.0f), 100, 100);

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
		if (!GetGameObject<CEnemy>(CHARACTER))
			CSceneManager::SetScene<CResult>();
	}
}