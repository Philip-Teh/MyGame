using namespace std;
//using namespace UI;

CUIManager::CUIManager()
{
	mpScore = make_unique<CScore>();
	mpStep = make_unique<CStep>();
	mpNumEnemy = make_unique<CNumEnemy>();
	mpPull = make_unique<CPull>();
	mpStageNum = make_unique<CStageNum>();

	mpMenu = make_unique<CMenu>();
	mpHelp = make_unique<CHelp>();
	mpKeyInfo = make_unique<CKeyInfo>();
	mpPause = make_unique<CPause>();
	mpReturn = make_unique<CReturn>();

	mpReset = make_unique<CReset>();
	mpExit = std::make_unique<CExit>();

}

CUIManager::~CUIManager()
{
	OutputDebugString("delete CUIMAnager\n");
}

void CUIManager::Update()
{
	mpMenu->Update();

	if (mpMenu->GetKeyUp())
	{
		mpHelp->Update();
		mpKeyInfo->Update();
		mpPause->Update();
		mpReturn->Update();
	}

	if (mpMenu->GetKeyDown())
	{
		mpHelp->TabCancel();
		mpKeyInfo->TabCancel();
		mpPause->TabCancel();
		mpReturn->TabCancel();
	}

	mpReset->Update();

	mpExit->Update();

	if (mpExit->GetPress())
	{
		if (CInput::GetKeyTrigger(VK_YEA))
			CExitTrigger::SetExit(true);
		else if (CInput::GetKeyTrigger(VK_NAY))
			mpExit->TabCancel();
	}
}

void CUIManager::Update(bool enable)
{
	if (enable)
	{
		mpNumEnemy->Update();
		mpPull->Update();
	}
}

void CUIManager::DrawStatus(int score,int step)
{
	mpScore->Draw(score);
	mpStep->Draw(step);
	
	//Draw::Texture(x - 340,y+YSIZE, x - 210, y + YSIZE*2, mtStep, 1);
}

void CUIManager::DrawEnemyStatus(int num)
{
	mpNumEnemy->Draw(num);
	mpPull->Draw();
}

void CUIManager::DrawStageNum(int num)
{
	mpStageNum->Draw(num);
}

void CUIManager::DrawMenu()
{
	mpMenu->Draw();
	mpHelp->Draw();
	mpKeyInfo->Draw();
	mpPause->Draw();
	mpReturn->Draw();

	mpReset->Draw();
	mpExit->Draw();

}

void CUIManager::Appear()
{
	mpNumEnemy->Appear();
	mpPull->Appear();
}

const bool& CUIManager::GetPress()
{
	return mpHelp->GetPress() || mpKeyInfo->GetPress() || mpPause->GetPress() || mpReturn->GetPress();
}