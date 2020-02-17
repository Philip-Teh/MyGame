//using namespace UI;


CReset::CReset()
{
	mFile = "asset/texture/ui/reset.png";

	mpPolygon = std::make_unique<CPolygon>();
	mpPolygon->Init(mFile, mWidth, mHeight);

	mMove = (int)SCREEN_HEIGHT;
	mkeyUpDown = mkeyUp = mkeyDown = false;
}

CReset::~CReset()
{
	mpPolygon->Uninit();

	OutputDebugString("delete CReset\n");
}

void CReset::Update()
{
	if (!mkeyUpDown && CInput::GetKeyTrigger('R')) {
		mkeyUp = true;
		mkeyDown = false;
	}

	if (mkeyUpDown && CInput::GetKeyTrigger('R')) {
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

void CReset::Draw()
{
	mpPolygon->Draw(XMFLOAT3(mPosition.x, mPosition.y + mMove, LAYER2));
}

void CReset::TabCancel(void)
{
	mkeyDown = true;
	mkeyUp = false;
	mMove += mSpeed;
}