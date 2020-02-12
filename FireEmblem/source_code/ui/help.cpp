//using namespace UI;

std::string gTexture = "asset/texture/ui/gamehelp.png";

CHelp::CHelp()
{
	mpPolygon = std::make_unique<CPolygon>();
	mpPolygon->Init(gTexture, 640, 480);

	mMove = (int)SCREEN_HEIGHT;
	mkeyUpDown = mkeyUp = mkeyDown = false;
}

CHelp::~CHelp()
{
	mpPolygon->Uninit();

	OutputDebugString("delete CHelp\n");
}

void CHelp::Update()
{
	if (!mkeyUpDown && CInput::GetKeyTrigger('1')) {
		mkeyUp = true;
		mkeyDown = false;
	}

	if (mkeyUpDown && CInput::GetKeyTrigger('1')) {
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

void CHelp::Draw()
{
	mpPolygon->Draw(XMFLOAT3(350.0f, 100.0f + mMove, LAYER1));
}

void CHelp::TabCancel(void)
{
	mkeyDown = true;
	mkeyUp = false;
	mMove += 100;
}