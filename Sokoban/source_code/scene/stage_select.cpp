using namespace std;


void CStageSelect::Init()
{
	mTexture[0] = "asset/texture/scene/stageselect.jpg";
	mTexture[1] = "asset/texture/scene/select.png";

	//ポインタ作成
	for (int i = 0; i < 2; i++)
	{
		mpPolygon[i] = make_unique<CPolygon>();
	}
	mpPolygon[0]->Init(mTexture[0],XMFLOAT3(0.0f, 0.0f, LAYER6), SCREEN_WIDTH, SCREEN_HEIGHT);
	mpPolygon[1]->Init(mTexture[1], XMFLOAT3(mPositionX, STATUS_POSITIONY, LAYER5), mWidth, mHeight);

	mpSelectButton = make_unique<CSelectButton>();

	//ローディングシーン終了
	CLoading::SetChange(false);

	//エンターインターフェース表示
	CEnter::SetEnable(true);
}

void CStageSelect::Uninit()
{
	for (int i = 0; i < 2; i++)
		mpPolygon[i]->Uninit();

	//エンターインターフェース非表示
	CEnter::SetEnable(false);
}

void CStageSelect::Update()
{
	mpSelectButton->Update();

	//ローディングシーン表示
	if (CInput::GetKeyTrigger(VK_RETURN))
		CLoading::SetEnable(true);

	//ジーンチェンジ
	if (CLoading::GetChange())
		CSceneManager::SetScene<CGame>();
}

void CStageSelect::Draw()
{
	for (int i = 0; i < 2; i++)
		mpPolygon[i]->Draw();

	mpSelectButton->Draw();
}