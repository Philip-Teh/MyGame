//using namespace StageSystem;

CStageOver::CStageOver()
{
	mpPolygon = std::make_unique<CPolygon>();
	mpPolygon->Init("asset/texture/ui/stageover.png", SCREEN_WIDTH, SCREEN_HEIGHT);

	SetMove();
}

CStageOver::~CStageOver()
{
	mpPolygon->Uninit();

	OutputDebugString("delete CStageClear\n");
}

void CStageOver::Update()
{
	mMove += 30;

	if (mMove >= SCREEN_WIDTH)
		mMove = SCREEN_WIDTH;
}

void CStageOver::Draw()
{
	mpPolygon->Draw(XMFLOAT3(0.0f, 0.0f, LAYER3), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	//mpPolygon->Draw(XMFLOAT3(SCREEN_WIDTH / 2.0f, 0.0f, 0.0f), SCREEN_WIDTH / 2, 0, mMoveX, SCREEN_HEIGHT);
	//mpPolygon->Draw(XMFLOAT3(0.0f, 0.0f, 0.0f), 0, 0, mMoveY, SCREEN_HEIGHT);
}

void CStageOver::SetMove()
{
	mMove = 0;
	CEnter::SetEnable(false);
}

bool CStageOver:: DrawCompleted(void)
{
	if (mMove == SCREEN_WIDTH)
	{
		CEnter::SetEnable(true);
		return true;
	}
	else
		return false;
}