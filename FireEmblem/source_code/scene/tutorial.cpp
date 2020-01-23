using namespace std;


void CTutorial::Init()
{
	mTexture[0] = "asset/texture/ui/tabinfo.png";
	mTexture[1] = "";
	mTexture[2] = "";

	//for (int i = 0; i < 3; i++)
	{
		mpPolygon[0] = make_unique<CPolygon>();
	}
	mpPolygon[0]->Init(mTexture[0],XMFLOAT3(0.0f, 0.0f, 0.1f), SCREEN_WIDTH, SCREEN_HEIGHT);
	//mpPolygon[1]->Init(mTexture[1], XMFLOAT3(0.0f, 0.0f, 0.2f), SCREEN_WIDTH, SCREEN_HEIGHT);
	//mpPolygon[2]->Init(mTexture[2], XMFLOAT3(400.0f, 450.0f, 0.0f), 400, 200);

}

void CTutorial::Uninit()
{
	//for (int i = 0; i < 3; i++)
		mpPolygon[0]->Uninit();
}

void CTutorial::Update()
{
	//mFrame++;
	if (mFrame >= 75)
		mFrame = 0;

	if(CInput::GetKeyTrigger(VK_RETURN))
	{
		CSceneManager::SetScene<CGame>();
	}
}

void CTutorial::Draw()
{
	//for (int i = 1; i >= 0; i--)
	{
		mpPolygon[0]->Draw();
	}
	//if (mFrame >= 30)
		//mpPolygon[2]->Draw();
}