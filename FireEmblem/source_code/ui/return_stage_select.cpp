//using namespace UI;


CReturnStageSelect::CReturnStageSelect()
{
	mFile = "asset/texture/ui/return.png";

	mpPolygon = std::make_unique<CPolygon>();
	mpPolygon->Init(mFile, mWidth, mHeight);

	mMove = (int)SCREEN_HEIGHT;
	mkeyUpDown = mkeyUp = mkeyDown = false;
}

CReturnStageSelect::~CReturnStageSelect()
{
	mpPolygon->Uninit();

	OutputDebugString("delete CReturnStageSelect\n");
}

void CReturnStageSelect::Update()
{
	if (!mkeyUpDown && CInput::GetKeyTrigger('3')) {
		mkeyUp = true;
		mkeyDown = false;
	}

	if (mkeyUpDown && CInput::GetKeyTrigger('3')) {
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

void CReturnStageSelect::Draw()
{
	mpPolygon->Draw(XMFLOAT3(mPosition.x, mPosition.y + mMove, LAYER2));
}

void CReturnStageSelect::TabCancel(void)
{
	mkeyDown = true;
	mkeyUp = false;
	mMove += mSpeed;
}