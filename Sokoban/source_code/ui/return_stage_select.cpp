//using namespace UI;


CReturnStageSelect::CReturnStageSelect()
{
	mFile = "asset/texture/ui/return.png";

	mpPolygon = std::make_unique<CPolygon>();
	mpPolygon->Init(mFile, mWidth, mHeight);

	mMove = (int)SCREEN_HEIGHT;
	mKeyUpDown = mKeyUp = mKeyDown = false;
}

CReturnStageSelect::~CReturnStageSelect()
{
	mpPolygon->Uninit();

	OutputDebugString("delete CReturnStageSelect\n");
}

void CReturnStageSelect::Update()
{
	if (!mKeyUpDown && CInput::GetKeyTrigger('3')) {
		mKeyUp = true;
		mKeyDown = false;
	}

	if (mKeyUpDown && CInput::GetKeyTrigger('3')) {
		mKeyDown = true;
		mKeyUp = false;
	}


	if (!mKeyDown && mKeyUp && !mKeyUpDown) {
		mMove -= mSpeed;
		if (mMove <= 0)
			mKeyUpDown = true;
	}

	if (mKeyDown && !mKeyUp && mKeyUpDown) {
		mMove += mSpeed;
		if (mMove >= SCREEN_HEIGHT)
			mKeyUpDown = false;
	}

	if (mMove <= 0)
		mMove = 0;
	if (mMove >= SCREEN_HEIGHT)
		mMove = SCREEN_HEIGHT;
}

void CReturnStageSelect::Draw()
{
	mpPolygon->Draw(XMFLOAT3(mPosition.x, mPosition.y + mMove, LAYER2));
}

void CReturnStageSelect::TabCancel(void)
{
	mKeyDown = true;
	mKeyUp = false;
	mMove += mSpeed;
}