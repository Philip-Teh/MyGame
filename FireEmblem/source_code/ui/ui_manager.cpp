using namespace std;
//using namespace UI;

CUIManager::CUIManager()
{
	mpScore = make_unique<CScore>();
	mpStep = make_unique<CStep>();
	mpNumEnemy = make_unique<CNumEnemy>();
	mpMenu = make_unique<CMenu>();
	mpHelp = make_unique<CHelp>();

	//mpKeyInfo = std::make_unique<KeyInfo>();
}

CUIManager::~CUIManager()
{
	OutputDebugString("delete CUIMAnager\n");
}

void CUIManager::Update()
{
	mpMenu->Update();

	if (mpMenu->GetKeyUp())
		mpHelp->Update();

	if (mpMenu->GetKeyDown())
		mpHelp->TabCancel();
}

void CUIManager::DrawStatus(int score,int step,int num)
{
	mpScore->Draw(score);
	mpStep->Draw(step);
	mpNumEnemy->Draw(num);
	//Draw::Texture(x - 340,y+YSIZE, x - 210, y + YSIZE*2, mtStep, 1);
}

void CUIManager::DrawStageNum(int x, int y, int num)
{
	//mpNumDraw->Draw(VECTOR2(x+550, y+25), VECTOR2(x + 550+XSIZE*3, y +25+YSIZE*3),2, num,1);
	//Draw::Texture(x + 10, y, x + 470, y + 240, mtStage, 1);
}

void CUIManager::DrawMenu()
{
	mpMenu->Draw();
	mpHelp->Draw();
}