using namespace std;

void CGameClear::Init()
{
	mTexture[0] = "asset/texture/scene/clear.png";
	mTexture[1] = "asset/texture/scene/gameclear.png";
	mTexture[2] = "asset/texture/scene/pp.png";

	for (int i = 0; i < 3; i++)
		mpPolygon[i] = make_unique<CPolygon>();

	mpPolygon[0]->Init(mTexture[0], SCREEN_WIDTH, SCREEN_HEIGHT);
	mpPolygon[1]->Init(mTexture[1], 700, 270);
	mpPolygon[2]->Init(mTexture[2], 150, 150);

	mMove = mMove1 = mMove2 = 0.0f;

	CLoading::SetChange(false);

}

void CGameClear::Uninit()
{
	for (int i = 0; i < 3; i++)
		mpPolygon[i]->Uninit();

	CEnter::SetEnable(false);
}

void CGameClear::Update()
{
	mMove += 100;
	if (mMove >= 500)
		mMove1 += 10;

	if (mMove1 >= 500)
		mMove2 += 10;

	mMove = MaxMove(mMove);
	mMove1 = MaxMove(mMove1);
	mMove2 = MaxMove(mMove2);

	if (mMove2 >= SCREEN_WIDTH)
		CEnter::SetEnable(true);

	if (CInput::GetKeyTrigger(VK_RETURN))
		CLoading::SetEnable(true);

	if(CLoading::GetChange())
		CSceneManager::SetScene<CResult>();
}

void CGameClear::Draw()
{
	mpPolygon[0]->Draw(XMFLOAT3(mMove - (float)SCREEN_WIDTH, 0.0f, LAYER6));
	mpPolygon[1]->Draw(XMFLOAT3(mMove1 - 750.0f, 10.0f, LAYER5));
	mpPolygon[2]->Draw(XMFLOAT3(mMove2 - 200.0f, 310.0f, LAYER4));
}

float CGameClear::MaxMove(float move)
{
	if (move >= SCREEN_WIDTH)
		move = SCREEN_WIDTH;

	return move;
}