//using namespace UI;


CExit::CExit()
{
	mFile = "asset/texture/ui/exit.png";

	mpPolygon = std::make_unique<CPolygon>();
	mpPolygon->Init(mFile, mWidth, mHeight);

	mMove = (int)SCREEN_HEIGHT;
	mkeyUpDown = mkeyUp = mkeyDown = false;
}

CExit::~CExit()
{
	mpPolygon->Uninit();

	OutputDebugString("delete CExit\n");
}

void CExit::Update()
{
	if (!mkeyUpDown && CInput::GetKeyTrigger(VK_ESCAPE)) {
		mkeyUp = true;
		mkeyDown = false;
	}

	if (mkeyUpDown && CInput::GetKeyTrigger(VK_ESCAPE)) {
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

void CExit::Draw()
{
	mpPolygon->Draw(XMFLOAT3(mPosition.x, mPosition.y + mMove, LAYER2));
}

void CExit::TabCancel(void)
{
	mkeyDown = true;
	mkeyUp = false;
	mMove += mSpeed;
}