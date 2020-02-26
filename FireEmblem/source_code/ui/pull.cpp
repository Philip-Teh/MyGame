using namespace std;

CPull::CPull()
{
	mFile = "asset/texture/ui/pull.png";
	mFile1 = "asset/texture/ui/lock.png";
	mFile2 = "asset/texture/ui/unlock.png";

	mpPolygon = make_unique<CPolygon>();
	mpPolygon1 = make_unique<CPolygon>();
	mpPolygon2 = make_unique<CPolygon>();

	mpPolygon->Init(mFile, STATUS_POLYGONX, STATUS_POLYGONY);

	mpPolygon1->Init(mFile1, NUMBER_WIDTH, NUMBER_HEIGHT);
	mpPolygon2->Init(mFile2, NUMBER_WIDTH, NUMBER_HEIGHT);

	mMove = 0;
	mKeyUp = mKeyDown = false;
	mLock = false;
}

CPull::~CPull()
{
	mpPolygon->Uninit();
	mpPolygon1->Uninit();
	mpPolygon2->Uninit();

	OutputDebugString("delete CPull\n");
}

void CPull::Update()
{
	if (!mKeyDown && !mKeyUp && CInput::GetKeyTrigger(VK_UP))
		mKeyUp = true;

	if (!mKeyUp && !mKeyDown && CInput::GetKeyTrigger(VK_DOWN))
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

void CPull::Draw()
{
	if (mLock)
		mpPolygon1->Draw(XMFLOAT3(STATUS_POSITIONX + NUMSPACEX, HIDDEN_STATUS_POSITIONY + mMove, LAYER8));
	else
		mpPolygon2->Draw(XMFLOAT3(STATUS_POSITIONX + NUMSPACEX, HIDDEN_STATUS_POSITIONY + mMove, LAYER8));

	mpPolygon->Draw(XMFLOAT3(STATUS_POSITIONX, HIDDEN_STATUS_POSITIONY - STATUS_POSITIONY + mMove, LAYER8));
}