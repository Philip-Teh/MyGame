using namespace std;

void CGameClear::Init()
{
	CAudioClip::Stop(CBGM::Game);
	CAudioClip::Play(true, CBGM::Clear);

	mTexture[0] = "asset/texture/scene/clear.png";
	mTexture[1] = "asset/texture/scene/gameclear.png";
	mTexture[2] = "asset/texture/scene/pp.png";

	for (int i = 0; i < 3; i++)
		mpPolygon[i] = make_unique<CPolygon>();

	mpPolygon[0]->Init(mTexture[0], SCREEN_WIDTH, SCREEN_HEIGHT);
	mpPolygon[1]->Init(mTexture[1], mGameClearSize.x, mGameClearSize.y);
	mpPolygon[2]->Init(mTexture[2], mCharacterSize.x, mCharacterSize.y);

	mMove1 = mMove2 = 0.0f;

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
	mMove1 += mSpeed;

	if (mMove1 >= mMax)
		mMove2 += mSpeed;

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
	mpPolygon[0]->Draw(XMFLOAT3(0.0f, 0.0f, LAYER6));
	mpPolygon[1]->Draw(XMFLOAT3(mMove1 - mGameClearPos.x, mGameClearPos.y, LAYER5));
	mpPolygon[2]->Draw(XMFLOAT3(mMove2 - mCharacterPos.x, mCharacterPos.y, LAYER4));
}

float CGameClear::MaxMove(float move)
{
	if (move >= SCREEN_WIDTH)
		move = SCREEN_WIDTH;

	return move;
}