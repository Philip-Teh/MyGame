using namespace std;
//using namespace UI;

CUIManager::CUIManager()
{
	mpScore = make_unique<CScore>();
	mpStep = make_unique<CStep>();
	mpNumEnemy = make_unique<CNumEnemy>();
	mpMenu = make_unique<CMenu>();
	//mpKeyInfo = std::make_unique<KeyInfo>();
	//mpGameHelp = std::make_unique<GameHelp>();

	mMove = 100;
	mKeyUpDown = mKeyUp = mKeyDown = false;
}

CUIManager::~CUIManager()
{
	OutputDebugString("delete CUIMAnager\n");
}

void CUIManager::Update()
{
	mpMenu->Update();
	/*if (!mKeyUpDown && Input::Trigger(KEY_INPUT_TAB)) {
		mKeyDown = false;
		mKeyUp = true;
	}
	if (mKeyUpDown && Input::Trigger(KEY_INPUT_TAB)) {
		mKeyDown = true;
		mKeyUp = false;
	}

	if (!mKeyUpDown && !mKeyDown && mKeyUp) {
		mMove-=10;
		if (mMove <= 0)
			mKeyUpDown = true;
	}
	if (mKeyUpDown && mKeyDown && !mKeyUp) {
		mMove+=10;
		if (mMove >= 100)
			mKeyUpDown = false;
	}

	if (mKeyUp)
	{
		mpKeyInfo->Update();
		mpGameHelp->Update();
	}
	if (mKeyDown)
	{
		mpKeyInfo->TabCancel();
		mpGameHelp->TabCancel();
	}*/
}

void CUIManager::DrawStatus(int score,int step,int num)
{
	mpScore->Draw(score);
	mpStep->Draw(step);
	mpNumEnemy->Draw(num);
	//Draw::Texture(x - 340,y+YSIZE, x - 210, y + YSIZE*2, mtStep, 1);
}

void CUIManager::DrawSN(int x, int y, int num)
{
	//mpNumDraw->Draw(VECTOR2(x+550, y+25), VECTOR2(x + 550+XSIZE*3, y +25+YSIZE*3),2, num,1);
	//Draw::Texture(x + 10, y, x + 470, y + 240, mtStage, 1);
}

void CUIManager::DrawMenu()
{
	mpMenu->Draw();

	//Draw::Texture(80, 1120 - mMove, 300, 1180 - mMove, mtMenu, 1);
	//DrawExtendGraph(50, (int)SCREENY-70+mMove, (int)SCREENX-50, (int)SCREENY+mMove, mtMenuBar, 1);
	//
	//mpGameHelp->Draw();
	//mpKeyInfo->Draw();
}