using namespace std;

void CResult::Init()
{
	mTexture[0] = "asset/texture/clear.png";
	mTexture[1] = "asset/texture/gameclear.png";
	mTexture[2] = "asset/texture/pp.png";

	for (int i = 0; i < 3; i++)
		mpPolygon[i] = make_unique<CPolygon>();

	mpPolygon[0]->Init(mTexture[0], XMFLOAT3(0.0f, 0.0f, 0.2f), SCREEN_WIDTH, SCREEN_HEIGHT);
	mpPolygon[1]->Init(mTexture[1], XMFLOAT3(0.0f, 0.0f, 0.1f), 700, 270);
	mpPolygon[2]->Init(mTexture[2], XMFLOAT3(0.0f, 0.0f, 0.0f), 150, 150);

	mMove = mMove1 = mMove2 = 0.0f;
}

void CResult::Uninit()
{
	for (int i = 0; i < 3; i++)
		mpPolygon[i]->Uninit();
}

void CResult::Update()
{
	mMove += 100;
	if (mMove >= 500)
		mMove1 += 10;

	if (mMove1 >= 500)
		mMove2 += 10;

	mMove = MaxMove(mMove);
	mMove1 = MaxMove(mMove1);
	mMove2 = MaxMove(mMove2);

	if (CInput::GetKeyTrigger(VK_RETURN))
	{
		CSceneManager::SetScene<CTitle>();
	}
}

void CResult::Draw()
{
	mpPolygon[0]->Draw(XMFLOAT3(mMove - (float)SCREEN_WIDTH, 0.0f, 0.2f));
	mpPolygon[1]->Draw(XMFLOAT3(mMove1 - 750.0f, 10.0f, 0.1f));
	mpPolygon[2]->Draw(XMFLOAT3(mMove2 - 200.0f, 310.0f, 0.0f));
}

float CResult::MaxMove(float move)
{
	if (move >= SCREEN_WIDTH)
		move = (float)SCREEN_WIDTH;

	return move;
}