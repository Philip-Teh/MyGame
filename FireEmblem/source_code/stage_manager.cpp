using namespace std;


void CStageManager::Init()
{
	mpMap = make_unique<CMap>();
	mpUIManager = make_unique<CUIManager>();
	mpStageClear = make_unique<CStageClear>();

	mStageClear = false;
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
		if (!mStageClear)
		{
			if (!mpUIManager->GetHelp())
				mpMap->Update();
			mpUIManager->Update();

			if (CInput::GetKeyTrigger('R'))
				CLoading::SetEnable(true);

			if (CLoading::GetChange())
				ResetStage();
		}


		if (mpMap->StageIsClear())
		{
			mStageClear = true;
			mpStageClear->Update();
		}
	}

	if (mStageClear && mpStageClear->DrawCompleted() && CInput::GetKeyTrigger(VK_RETURN))
		CLoading::SetEnable(true);

	if (CLoading::GetChange())
		NextStage();
}

void CStageManager::Draw()
{
	if (!CGameStatus::GetGameClear())
	{
		mpMap->Draw();
		mpUIManager->DrawStatus(CGameStatus::GetScore(), mpMap->GetStep(), mpMap->GetNumEnemy());
		mpUIManager->DrawMenu();

		if (mStageClear)
			mpStageClear->Draw();
	}
}

void CStageManager::NextStage()
{
	mpMap->Uninit();

	CGameStatus::SetStageClear(mStage);
	mStage++;
	mStageClear = false;
	ScoreCaculate();

	if (mStage > MaXStage)
		CGameStatus::SetGameClear(true);

	if (!CGameStatus::GetGameClear())
	{
		mpStageClear->SetMove();
		mpMap->Load(mStage);
		mpMap->Init();
	}

	CLoading::SetChange(false);
}

void CStageManager::ResetStage()
{
	mpMap->Uninit();
	mpMap->Load(mStage);
	mpMap->Init();

	CLoading::SetChange(false);
}

void CStageManager::ScoreCaculate()
{
	if (mStage >= CGameStatus::GetStageClear())
	{
		if (mStage * 100 - mpMap->GetStep() > 0)
			CGameStatus::PlusScore(mStage * 100 - mpMap->GetStep());
	}
}