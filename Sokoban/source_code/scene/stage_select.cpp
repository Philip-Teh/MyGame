using namespace std;


void CStageSelect::Init()
{
	mTexture[0] = "asset/texture/scene/stageselect.jpg";
	mTexture[1] = "asset/texture/scene/select.png";

	for (int i = 0; i < 2; i++)
	{
		mpPolygon[i] = make_unique<CPolygon>();
	}
	mpPolygon[0]->Init(mTexture[0],XMFLOAT3(0.0f, 0.0f, LAYER6), SCREEN_WIDTH, SCREEN_HEIGHT);
	mpPolygon[1]->Init(mTexture[1], XMFLOAT3(mPositionX, STATUS_POSITIONY, LAYER5), mWidth, mHeight);

	mpSelectButton = make_unique<CSelectButton>();

	CLoading::SetChange(false);
	CEnter::SetEnable(true);
}

void CStageSelect::Uninit()
{
	for (int i = 0; i < 2; i++)
		mpPolygon[i]->Uninit();

	CEnter::SetEnable(false);
}

void CStageSelect::Update()
{
	mpSelectButton->Update();

	if (CInput::GetKeyTrigger(VK_RETURN))
		CLoading::SetEnable(true);

	if (CLoading::GetChange())
		CSceneManager::SetScene<CGame>();
}

void CStageSelect::Draw()
{
	for (int i = 0; i < 2; i++)
		mpPolygon[i]->Draw();

	mpSelectButton->Draw();
}