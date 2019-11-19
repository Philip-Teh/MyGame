

void CTitle::Init()
{
	mTexture = "asset/GameStart.png";

	mpPolygon = new CPolygon();
	mpPolygon->Init();
	mpPolygon->Create(mTexture,XMFLOAT3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
}

void CTitle::Uninit()
{
	mpPolygon->Uninit();
	delete mpPolygon;
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
	mpPolygon->Draw();
}