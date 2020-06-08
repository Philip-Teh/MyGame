using namespace std;

CMenu::CMenu()
{
	mFile = "asset/texture/ui/tab.png";
	mFile1 = "asset/texture/ui/menubar.png";

	//ポインタ作成
	mpPolygon = make_unique<CPolygon>();
	mpPolygon1 = make_unique<CPolygon>();

	mpPolygon->Init(mFile, 200, 50);
	mpPolygon1->Init(mFile1, SCREEN_WIDTH, 50);

	mMove = 100;
	mKeyUpDown = mKeyUp = mKeyDown = false;
}

CMenu::~CMenu()
{
	mpPolygon->Uninit();
	mpPolygon1->Uninit();

	OutputDebugString("delete CMenu\n");
}

void CMenu::Update()
{
	//同じキーで開くことと閉じることを実行する
	//開く
	if (!mKeyUpDown && CInput::GetKeyTrigger(VK_TAB)) {
		mKeyDown = false;
		mKeyUp = true;
	}

	//閉じる
	if (mKeyUpDown && CInput::GetKeyTrigger(VK_TAB)) {
		mKeyDown = true;
		mKeyUp = false;
	}

	//開く移動処理
	if (!mKeyUpDown && !mKeyDown && mKeyUp) {
		mMove -= 10;
		if (mMove <= 0)
			mKeyUpDown = true;
	}

	//閉じる移動処理
	if (mKeyUpDown && mKeyDown && !mKeyUp) {
		mMove += 10;
		if (mMove >= 100)
			mKeyUpDown = false;
	}
}

void CMenu::Draw()
{
	mpPolygon->Draw(XMFLOAT3(30.0f, 750.0f - mMove, LAYER6));
	mpPolygon1->Draw(XMFLOAT3(0.0f, 650.0f + mMove, LAYER4));
}