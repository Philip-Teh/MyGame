using namespace std;


void CTitle::Init()
{
	mTexture[0] = "asset/texture/title.png";
	mTexture[1] = "asset/texture/title.jpg";
	mTexture[2] = "asset/texture/enter.png";

	for (int i = 0; i < 3; i++)
	{
		mpPolygon[i] = make_unique<CPolygon>();
	}
	mpPolygon[0]->Init(mTexture[0],XMFLOAT3(0.0f, 0.0f, 0.1f), SCREEN_WIDTH, SCREEN_HEIGHT);
	mpPolygon[1]->Init(mTexture[1], XMFLOAT3(0.0f, 0.0f, 0.2f), SCREEN_WIDTH, SCREEN_HEIGHT);
	mpPolygon[2]->Init(mTexture[2], XMFLOAT3(400.0f, 450.0f, 0.0f), 400, 200);

}

void CTitle::Uninit()
{
	for (int i = 0; i < 3; i++)
		mpPolygon[i]->Uninit();
}

void CTitle::Update()
{
	mFrame++;
	if (mFrame >= 75)
		mFrame = 0;

	if(CInput::GetKeyTrigger(VK_RETURN))
	{
		CSceneManager::SetScene<CTutorial>();
	}
}

void CTitle::Draw()
{
	for (int i = 1; i >= 0; i--)
	{
		mpPolygon[i]->Draw();
	}
	if (mFrame >= 30)
		mpPolygon[2]->Draw();
}