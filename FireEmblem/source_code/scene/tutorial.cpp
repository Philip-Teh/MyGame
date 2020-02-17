using namespace std;


void CTutorial::Init()
{
	mTexture = "asset/texture/ui/key_info1.png";


	//for (int i = 0; i < 3; i++)
	{
		mpPolygon = make_unique<CPolygon>();
	}
	mpPolygon->Init(mTexture,XMFLOAT3(0.0f, 0.0f, LAYER6), SCREEN_WIDTH, SCREEN_HEIGHT);
	//mpPolygon[1]->Init(mTexture[1], XMFLOAT3(0.0f, 0.0f, 0.2f), SCREEN_WIDTH, SCREEN_HEIGHT);
	//mpPolygon[2]->Init(mTexture[2], XMFLOAT3(400.0f, 450.0f, 0.0f), 400, 200);

	CLoading::SetChange(false);
}

void CTutorial::Uninit()
{
	//for (int i = 0; i < 3; i++)
		mpPolygon->Uninit();
}

void CTutorial::Update()
{
	//mFrame++;
	if (mFrame >= 75)
		mFrame = 0;

	if (CInput::GetKeyTrigger(VK_RETURN))
		CLoading::SetEnable(true);

	if (CLoading::GetChange())
		CSceneManager::SetScene<CStageSelect>();
}

void CTutorial::Draw()
{
	//for (int i = 1; i >= 0; i--)
	{
		mpPolygon->Draw();
	}
	//if (mFrame >= 30)
		//mpPolygon[2]->Draw();
}