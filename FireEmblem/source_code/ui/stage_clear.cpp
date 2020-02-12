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
	mMoveX += 30;
	mMoveY-=5;

	if (mMoveX >= SCREEN_WIDTH)
		mMoveX = SCREEN_WIDTH;

	if (mMoveY <= 0)
		mMoveY = 0;
}

void CStageClear::Draw()
{
	mpPolygon->Draw(XMFLOAT3(0.0f, 0.0f, LAYER2), 0, 0, mMoveX, SCREEN_HEIGHT);
	//mpPolygon->Draw(XMFLOAT3(SCREEN_WIDTH / 2.0f, 0.0f, 0.0f), SCREEN_WIDTH / 2, 0, mMoveX, SCREEN_HEIGHT);
	//mpPolygon->Draw(XMFLOAT3(0.0f, 0.0f, 0.0f), 0, 0, mMoveY, SCREEN_HEIGHT);
}

void CStageClear::SetMove()
{
	mMoveX = 0;
	mMoveY = SCREEN_WIDTH / 2;
}

bool CStageClear:: DrawCompleted(void)
{
	if (mMoveX == SCREEN_WIDTH && mMoveY == 0)
		return true;
	else
		return false;
}