//using namespace StageSystem;

CStageClear::CStageClear()
{
	mpPolygon = std::make_unique<CPolygon>();
	mpPolygon->Init("asset/texture/ui/stageclear.png", SCREEN_WIDTH, SCREEN_HEIGHT);

	SetMove();

}

CStageClear::~CStageClear()
{
	mpPolygon->Uninit();

	OutputDebugString("delete CStageClear\n");
}

void CStageClear::Update()
{
	mMove += 30;

	if (mMove >= SCREEN_WIDTH)
		mMove = SCREEN_WIDTH;
}

void CStageClear::Draw()
{
	mpPolygon->Draw(XMFLOAT3(0.0f, 0.0f, LAYER3), 0, 0, mMove, SCREEN_HEIGHT);
	//mpPolygon->Draw(XMFLOAT3(SCREEN_WIDTH / 2.0f, 0.0f, 0.0f), SCREEN_WIDTH / 2, 0, mMoveX, SCREEN_HEIGHT);
	//mpPolygon->Draw(XMFLOAT3(0.0f, 0.0f, 0.0f), 0, 0, mMoveY, SCREEN_HEIGHT);
}

void CStageClear::SetMove()
{
	mMove = 0;
	CEnter::SetEnable(false);
}

bool CStageClear:: DrawCompleted(void)
{
	if (mMove == SCREEN_WIDTH)
	{
		CEnter::SetEnable(true);
		return true;
	}
	else
		return false;
}