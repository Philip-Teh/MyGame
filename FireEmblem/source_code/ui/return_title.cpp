//using namespace UI;


CReturnTitle::CReturnTitle()
{
	mFile = "asset/texture/ui/returntitle.png";

	mpPolygon = std::make_unique<CPolygon>();
	mpPolygon->Init(mFile, mWidth, mHeight);

	mMove = (int)SCREEN_HEIGHT;
	mkeyUpDown = mkeyUp = mkeyDown = false;
}

CReturnTitle::~CReturnTitle()
{
	mpPolygon->Uninit();

	OutputDebugString("delete CReturnTitle\n");
}

void CReturnTitle::Update()
{
	if (!mkeyUpDown && CInput::GetKeyTrigger('4')) {
		mkeyUp = true;
		mkeyDown = false;
	}

	if (mkeyUpDown && CInput::GetKeyTrigger('4')) {
		mkeyDown = true;
		mkeyUp = false;
	}


	if (!mkeyDown && mkeyUp && !mkeyUpDown) {
		mMove -= mSpeed;
		if (mMove <= 0)
			mkeyUpDown = true;
	}

	if (mkeyDown && !mkeyUp && mkeyUpDown) {
		mMove += mSpeed;
		if (mMove >= SCREEN_HEIGHT)
			mkeyUpDown = false;
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
	mkeyDown = true;
	mkeyUp = false;
	mMove += mSpeed;
}