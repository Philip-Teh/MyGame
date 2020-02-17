//using namespace UI;


CKeyInfo::CKeyInfo()
{
	mFile = "asset/texture/ui/key_info1.png";

	mpPolygon = std::make_unique<CPolygon>();
	mpPolygon->Init(mFile, SCREEN_WIDTH, SCREEN_HEIGHT);

	mMove = (int)SCREEN_HEIGHT;
	mkeyUpDown = mkeyUp = mkeyDown = false;
}

CKeyInfo::~CKeyInfo()
{
	mpPolygon->Uninit();

	OutputDebugString("delete CKeyInfo\n");
}

void CKeyInfo::Update()
{
	if (!mkeyUpDown && CInput::GetKeyTrigger('2')) {
		mkeyUp = true;
		mkeyDown = false;
	}

	if (mkeyUpDown && CInput::GetKeyTrigger('2')) {
		mkeyDown = true;
		mkeyUp = false;
	}


	if (!mkeyDown && mkeyUp && !mkeyUpDown) {
		mMove -= 100;
		if (mMove <= 0)
			mkeyUpDown = true;
	}

	if (mkeyDown && !mkeyUp && mkeyUpDown) {
		mMove += 100;
		if (mMove >= SCREEN_HEIGHT)
			mkeyUpDown = false;
	}

	if (mMove <= 0)
		mMove = 0;
	if (mMove >= SCREEN_HEIGHT)
		mMove = SCREEN_HEIGHT;
}

void CKeyInfo::Draw()
{
	mpPolygon->Draw(XMFLOAT3(0.0f, 0.0f + mMove, LAYER1));
}

void CKeyInfo::TabCancel(void)
{
	mkeyDown = true;
	mkeyUp = false;
	mMove += 100;
}