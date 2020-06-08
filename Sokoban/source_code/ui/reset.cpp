//using namespace UI;


CReset::CReset()
{
	mFile = "asset/texture/ui/reset.png";

	//ポインタ作成
	mpPolygon = std::make_unique<CPolygon>();
	mpPolygon->Init(mFile, mWidth, mHeight);

	mMove = (int)SCREEN_HEIGHT;
	mKeyUpDown = mKeyUp = mKeyDown = false;
}

CReset::~CReset()
{
	mpPolygon->Uninit();

	OutputDebugString("delete CReset\n");
}

void CReset::Update()
{
	//同じキーで開くことと閉じることを実行する
	//開く
	if (!mKeyUpDown && CInput::GetKeyTrigger(VK_R)) {
		mKeyUp = true;
		mKeyDown = false;
	}

	//閉じる
	if (mKeyUpDown && CInput::GetKeyTrigger(VK_R)) {
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
}

void CReset::Draw()
{
	mpPolygon->Draw(XMFLOAT3(mPosition.x, mPosition.y + mMove, LAYER2));
}

void CReset::TabCancel(void)
{
	mKeyDown = true;
	mKeyUp = false;
	mMove += mSpeed;
}