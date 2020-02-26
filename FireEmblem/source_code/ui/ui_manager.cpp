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
	mpTitle = make_unique<CReturnTitle>();
	mpReturn = make_unique<CReturnStageSelect>();

	mpReset = make_unique<CReset>();
	mpExit = make_unique<CExit>();

	mpPause = make_unique<CPause>();
}

CUIManager::~CUIManager()
{
	OutputDebugString("delete CUIMAnager\n");
}

void CUIManager::Update()
{
	mpMenu->Update();
	mpHelp->FirstDrawCancel();

	if (mpMenu->GetKeyUp())
	{
		mpHelp->Update();
		mpKeyInfo->Update();
		mpTitle->Update();
		mpReturn->Update();
	}

	if (mpMenu->GetKeyDown())
	{
		mpHelp->TabCancel();
		mpKeyInfo->TabCancel();
		mpTitle->TabCancel();
		mpReturn->TabCancel();
	}

	mpReset->Update();

	mpExit->Update();

	if (mpExit->GetKeyUp())
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
	if (mpMenu->GetKeyUp())
		mpPause->Draw();

	mpMenu->Draw();
	mpHelp->Draw();
	mpKeyInfo->Draw();
	mpTitle->Draw();
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
	return mpMenu->GetKeyUp();
}