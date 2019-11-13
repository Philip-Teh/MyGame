

void CTitle::Init()
{
	texture = "asset/GameStart.png";

	polygon = new CPolygon();
	polygon->Init();
	polygon->Create(texture,XMFLOAT3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
}

void CTitle::Uninit()
{
	polygon->Uninit();
	delete polygon;
}

void CTitle::Update()
{
	if(CInput::GetKeyTrigger(VK_RETURN))
	{
		CSceneManager::SetScene<CGame>();
	}
}

void CTitle::Draw()
{
	polygon->Draw();
}