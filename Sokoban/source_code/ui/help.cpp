//using namespace UI;

CHelp::CHelp()
{
	mFile = "asset/texture/ui/help.png";

	//ポインタ作成
	mpPolygon = std::make_unique<CPolygon>();
	mpPolygon->Init(mFile, mWidth, mHeight);

	mMoveFirst = 0;
	mKeyEnter = false;

	mMove = (int)SCREEN_HEIGHT;
	mKeyUpDown = mKeyUp = mKeyDown = false;
}

CHelp::~CHelp()
{
	mpPolygon->Uninit();

	OutputDebugString("delete CHelp\n");
}

void CHelp::Update()
{
	//同じキーで開くことと閉じることを実行する
	//開く
	if (!mKeyUpDown && CInput::GetKeyTrigger(VK_NUM1)) {
		mKeyUp = true;
		mKeyDown = false;
	}

	//閉じる
	if (mKeyUpDown && CInput::GetKeyTrigger(VK_NUM1)) {
		mKeyDown = true;
		mKeyUp = false;
	}

	//開く移動処理
	if (!mKeyDown && mKeyUp && !mKeyUpDown) {
		mMove -= mSpeed;
		if (mMove <= 0)
			mKeyUpDown = true;
	}

	//閉じる移動処理
	if (mKeyDown && !mKeyUp && mKeyUpDown) {
		mMove += mSpeed;
		if (mMove >= SCREEN_HEIGHT)
			mKeyUpDown = false;
	}

	if (mMove <= 0)
		mMove = 0;
	if (mMove >= SCREEN_HEIGHT)
		mMove = SCREEN_HEIGHT;

	if (mMoveFirst >= SCREEN_HEIGHT)
		mMoveFirst = SCREEN_HEIGHT;
}

void CHelp::Draw()
{
	mpPolygon->Draw(XMFLOAT3(mPosition.x, mPosition.y + mMove, LAYER1));
}

void CHelp::FirstDraw()
{
	mpPolygon->Draw(XMFLOAT3(mPosition.x, mPosition.y + mMoveFirst, LAYER2));
}

void CHelp::TabCancel(void)
{
	mKeyDown = true;
	mKeyUp = false;
	mMove += mSpeed;
}

void CHelp::FirstDrawCancel()
{
	if (mKeyEnter)
	{
		mMoveFirst += mSpeed;
		CEnter::SetEnable(false);
	}
	else
	{
		mMoveFirst = 0;
		CEnter::SetEnable(true);
	}
}