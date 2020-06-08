using namespace std;


void CTutorial::Init()
{
	mTexture = "asset/texture/ui/key_info1.png";

	//ポインタ作成
	mpPolygon = make_unique<CPolygon>();
	mpPolygon->Init(mTexture,XMFLOAT3(0.0f, 0.0f, LAYER6), SCREEN_WIDTH, SCREEN_HEIGHT);

	//ローディングシーン終了
	CLoading::SetChange(false);

	//エンターインターフェース表示
	CEnter::SetEnable(true);
}

void CTutorial::Uninit()
{
	mpPolygon->Uninit();

	//エンターインターフェース非表示
	CEnter::SetEnable(false);
}

void CTutorial::Update()
{
	//ローディングシーン表示
	if (CInput::GetKeyTrigger(VK_RETURN))
		CLoading::SetEnable(true);

	//シーンチェンジ
	if (CLoading::GetChange())
		CSceneManager::SetScene<CStageSelect>();
}

void CTutorial::Draw()
{
	mpPolygon->Draw();
}