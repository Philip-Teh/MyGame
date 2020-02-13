using namespace std;

CNumEnemy::CNumEnemy()
{
	mFile = "asset/texture/ui/enemy.png";
	mpPolygon = make_unique<CPolygon>();
	mpPolygon->Init(mFile,STATUS_POLYGONX, STATUS_POLYGONY);

	mpNumDraw = make_unique<CNumDraw>();
	mpNumDraw->Init(NUMBER_SIZEX, NUMBER_HEIGHT);

	mMove = 0;
	mKeyUp = mKeyDown = false;
}

CNumEnemy::~CNumEnemy()
{
	mpPolygon->Uninit();
	mpNumDraw->Uninit();

	OutputDebugString("delete CScore\n");
}

void CNumEnemy::Update()
{
	if (!mKeyDown && !mKeyUp && CInput::GetKeyTrigger(VK_UP))
		mKeyUp = true;

	if (!mKeyDown && !mKeyUp && CInput::GetKeyTrigger(VK_DOWN))
		mKeyDown = true;

	if (mKeyUp && mMove >= 0)
	{
		mMove -= mSpeed;
		if (mMove <= 0)
		{
			mKeyUp = false;
			mMove = 0;
		}
	}
	if (mKeyDown && mMove <= mMaxMove)
	{
		mMove += mSpeed;
		if (mMove >= mMaxMove)
		{
			mKeyDown = false;
			mMove = mMaxMove;
		}
	}
}

void CNumEnemy::Draw(int num)
{
	mpPolygon->Draw(XMFLOAT3(STATUS_POSITIONX, (float)mMove - STATUS_POSITIONY + HIDDEN_STATUS_POSITIONY, LAYER6));
	mpNumDraw->Draw(XMFLOAT3(STATUS_POSITIONX + NUMSPACEX, (float)mMove + HIDDEN_STATUS_POSITIONY, LAYER6), num);
}