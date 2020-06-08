//using namespace UI;


CExit::CExit()
{
	mFile = "asset/texture/ui/exit.png";

	//ポインタ作成
	mpPolygon = std::make_unique<CPolygon>();
	mpPolygon->Init(mFile, mWidth, mHeight);

	mMove = (int)SCREEN_HEIGHT;
	mKeyUpDown = mKeyUp = mKeyDown = false;
}

CExit::~CExit()
{
	mpPolygon->Uninit();

	OutputDebugString("delete CExit\n");
}

void CExit::Update()
{
	//同じキーで開くことと閉じることを実行する
	//開く
	if (!mKeyUpDown && CInput::GetKeyTrigger(VK_ESCAPE)) {
		mKeyUp = true;
		mKeyDown = false;
	}

	//閉じる
	if (mKeyUpDown && CInput::GetKeyTrigger(VK_ESCAPE)) {
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

void CExit::Draw()
{
	mpPolygon->Draw(XMFLOAT3(mPosition.x, mPosition.y + mMove, LAYER2));
}

void CExit::TabCancel()
{
	mKeyDown = true;
	mKeyUp = false;
	mMove += mSpeed;
}