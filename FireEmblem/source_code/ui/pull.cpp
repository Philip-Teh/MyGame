
CPull::CPull()
{
	mFile[0] = "asset/texture/ui/pull.png";
	mFile[1] = "asset/texture/ui/lock.png";
	mFile[2] = "asset/texture/ui/unlock.png";

	for (int i = 0; i < 3; i++)
		mpPolygon[i] = std::make_unique<CPolygon>();

	mpPolygon[0]->Init(mFile[0], STATUS_POLYGONX, STATUS_POLYGONY);

	mpPolygon[1]->Init(mFile[1], NUMBER_WIDTH, NUMBER_HEIGHT);
	mpPolygon[2]->Init(mFile[2], NUMBER_WIDTH, NUMBER_HEIGHT);

	mMove = 0;
	mKeyUp = mKeyDown = false;
	mLock = false;
}

CPull::~CPull()
{
	for (int i = 0; i < 3; i++)
		mpPolygon[i]->Uninit();

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
		mpPolygon[1]->Draw(XMFLOAT3(STATUS_POSITIONX + NUMSPACEX, HIDDEN_STATUS_POSITIONY + mMove, LAYER7));
	else
		mpPolygon[2]->Draw(XMFLOAT3(STATUS_POSITIONX + NUMSPACEX, HIDDEN_STATUS_POSITIONY + mMove, LAYER7));

	mpPolygon[0]->Draw(XMFLOAT3(STATUS_POSITIONX, HIDDEN_STATUS_POSITIONY - STATUS_POSITIONY + mMove, LAYER7));
}