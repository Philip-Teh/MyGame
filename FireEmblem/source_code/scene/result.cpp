

void CResult::Init()
{
	mTexture = "asset/gameclear.png";

	mpPolygon = new CPolygon();
	mpPolygon->Init();
	mpPolygon->Create(mTexture,XMFLOAT3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
}

void CResult::Uninit()
{
	mpPolygon->Uninit();
	delete mpPolygon;
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
	mpPolygon->Draw();
}