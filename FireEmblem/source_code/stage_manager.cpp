using namespace std;


void CStageManager::Init()
{
	mpMap = make_unique<CMap>();
	mpUIManager = make_unique<CUIManager>();

	stageclear = false;
	mStage = CGameStatus::GetStageChoose();

	mpMap->Load(mStage);
	mpMap->Init();
}

void CStageManager::Uninit()
{
	OutputDebugString("delete CStageManager\n");
}

void CStageManager::Update()
{
	if (!CGameStatus::GetGameClear())
	{
		mpMap->Update();
		mpUIManager->Update();

		if (CInput::GetKeyTrigger('R'))
			ResetStage();

		if (mpMap->StageIsClear())
			stageclear = true;

		if (stageclear && !CGameStatus::GetGameClear())
			NextStage();
	}
}

void CStageManager::Draw()
{
	if (!CGameStatus::GetGameClear())
	{
		mpMap->Draw();
		mpUIManager->DrawStatus(CGameStatus::GetScore(), mpMap->GetStep(), mpMap->GetNumEnemy());
		mpUIManager->DrawMenu();
	}
}

void CStageManager::NextStage()
{
	mpMap->Uninit();

	CGameStatus::SetStageClear(mStage);
	mStage++;
	stageclear = false;
	ScoreCaculate();

	if (mStage > MaXStage)
		CGameStatus::SetGameClear(true);

	if (!CGameStatus::GetGameClear())
	{
		mpMap->Load(mStage);
		mpMap->Init();
	}
}

void CStageManager::ResetStage()
{
	mpMap->Uninit();
	mpMap->Load(mStage);
	mpMap->Init();
}

void CStageManager::ScoreCaculate()
{
	if (mStage >= CGameStatus::GetStageClear())
	{
		if (mStage * 100 - mpMap->GetStep() > 0)
			CGameStatus::PlusScore(mStage * 100 - mpMap->GetStep());
	}
}