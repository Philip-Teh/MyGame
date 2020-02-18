using namespace std;

CMenu::CMenu()
{
	mFile[0] = "asset/texture/ui/tab.png";
	mFile[1] = "asset/texture/ui/menubar.png";

	for (int i = 0; i < 2; i++)
		mpPolygon[i] = make_unique<CPolygon>();

	mpPolygon[0]->Init(mFile[0], 200, 50);
	mpPolygon[1]->Init(mFile[1], SCREEN_WIDTH, 50);

	mMove = 100;
	mKeyTrigger = mKeyUp = mKeyDown = false;
}

CMenu::~CMenu()
{
	for (int i = 0; i < 2; i++)
		mpPolygon[i]->Uninit();

	OutputDebugString("delete CMenu\n");
}

void CMenu::Update()
{
	if (!mKeyTrigger && CInput::GetKeyTrigger(VK_TAB)) {
		mKeyDown = false;
		mKeyUp = true;
	}
	if (mKeyTrigger && CInput::GetKeyTrigger(VK_TAB)) {
		mKeyDown = true;
		mKeyUp = false;
	}

	if (!mKeyTrigger && !mKeyDown && mKeyUp) {
		mMove -= 10;
		if (mMove <= 0)
			mKeyTrigger = true;
	}
	if (mKeyTrigger && mKeyDown && !mKeyUp) {
		mMove += 10;
		if (mMove >= 100)
			mKeyTrigger = false;
	}
}

void CMenu::Draw()
{
	mpPolygon[0]->Draw(XMFLOAT3(30.0f, 750.0f - mMove, LAYER4));
	mpPolygon[1]->Draw(XMFLOAT3(0.0f, 650.0f + mMove, LAYER4));
}