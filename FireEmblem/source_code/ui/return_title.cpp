//using namespace UI;


CReturnTitle::CReturnTitle()
{
	mFile = "asset/texture/ui/returntitle.png";

	mpPolygon = std::make_unique<CPolygon>();
	mpPolygon->Init(mFile, mWidth, mHeight);

	mMove = (int)SCREEN_HEIGHT;
	mKeyUpDown = mKeyUp = mKeyDown = false;
}

CReturnTitle::~CReturnTitle()
{
	mpPolygon->Uninit();

	OutputDebugString("delete CReturnTitle\n");
}

void CReturnTitle::Update()
{
	if (!mKeyUpDown && CInput::GetKeyTrigger('4')) {
		mKeyUp = true;
		mKeyDown = false;
	}

	if (mKeyUpDown && CInput::GetKeyTrigger('4')) {
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

void CReturnTitle::Draw()
{
	mpPolygon->Draw(XMFLOAT3(mPosition.x, mPosition.y + mMove, LAYER2));
}

void CReturnTitle::TabCancel(void)
{
	mKeyDown = true;
	mKeyUp = false;
	mMove += mSpeed;
}