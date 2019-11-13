

void CResult::Init()
{
	texture = "asset/gameclear.png";

	polygon = new CPolygon();
	polygon->Init();
	polygon->Create(texture,XMFLOAT3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
}

void CResult::Uninit()
{
	polygon->Uninit();
	delete polygon;
}

void CResult::Update()
{
	if (CInput::GetKeyTrigger(VK_RETURN))
	{
		CSceneManager::SetScene<CTitle>();
	}
}

void CResult::Draw()
{
	polygon->Draw();
}