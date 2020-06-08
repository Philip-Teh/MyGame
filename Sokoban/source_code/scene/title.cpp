using namespace std;


void CTitle::Init()
{
	//タイトル音声を放送開始
	CAudioClip::Play(true, CBGM::Start);

	//初期ゲームステータスを設定
	CGameStatus::SetGameClear(false);
	CGameStatus::SetGameOver(false);
	CGameStatus::SetScore(0);
	CGameStatus::SetStageClear(1);

	mTexture[0] = "asset/texture/scene/title.png";
	mTexture[1] = "asset/texture/scene/title.jpg";
	mTexture[2] = "asset/texture/scene/enter.png";

	//ポインタ作成
	for (int i = 0; i < 3; i++)
	{
		mpPolygon[i] = make_unique<CPolygon>();
	}
	mpPolygon[0]->Init(mTexture[0],XMFLOAT3(0.0f, 0.0f, LAYER5), SCREEN_WIDTH, SCREEN_HEIGHT);
	mpPolygon[1]->Init(mTexture[1], XMFLOAT3(0.0f, 0.0f, LAYER6), SCREEN_WIDTH, SCREEN_HEIGHT);
	mpPolygon[2]->Init(mTexture[2], XMFLOAT3(400.0f, 450.0f, LAYER4), 400, 200);

	//ローディングシーン終了
	CLoading::SetChange(false);
}

void CTitle::Uninit()
{
	for (int i = 0; i < 3; i++)
		mpPolygon[i]->Uninit();

	OutputDebugString("delete CTitle\n");
}

void CTitle::Update()
{
	mFrame++;
	if (mFrame >= 75)
		mFrame = 0;

	//ローディングシーン表示
	if (CInput::GetKeyTrigger(VK_RETURN))
		CLoading::SetEnable(true);

	//シーンチェンジ
	if (CLoading::GetChange())
		CSceneManager::SetScene<CTutorial>();
	
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