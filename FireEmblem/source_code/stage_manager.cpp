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

	if (mpMap->GetMaxEnemy() > 0)
	{
		mpUIManager->Appear();
		mEnemyAppear = true;
	}
	else
		mEnemyAppear = false;

	mPlusScore = false;
}

void CStageManager::Uninit()
{
	mpMap->Uninit();

	OutputDebugString("delete CStageManager\n");
}

void CStageManager::Update()
{
	if (!CGameStatus::GetGameClear() && !CGameStatus::GetGameOver())
	{
		if (!mStageClear)
		{
			if (!mpUIManager->GetPress()&& !mpUIManager->GetReset())
				mpMap->Update();

			mpUIManager->Update();
			mpUIManager->Update(mEnemyAppear);

			if (mpUIManager->GetReset())
			{
				if (CInput::GetKeyTrigger(VK_YEA))
					CLoading::SetEnable(true);
				else if (CInput::GetKeyTrigger(VK_NAY))
					mpUIManager->ResetNay();

				if (CLoading::GetChange())
				{
					mpUIManager->ResetNay();
					ResetStage();
				}
			}
		}

		if (mpMap->GetNumEnemy() == 0)
			mpUIManager->SetLock(true);
		else
			mpUIManager->SetLock(false);

		if (mpMap->StageIsClear())
		{
			mStageClear = true;
			mpStageClear->Update();
		}
	}

	if (mStageClear && mpStageClear->DrawCompleted())
	{
		if (!mPlusScore)
			ScoreCaculate();

		if (CInput::GetKeyTrigger(VK_RETURN))
			CLoading::SetEnable(true);

		if (CLoading::GetChange())
			NextStage();
	}
}

void CStageManager::Draw()
{
	if (!CGameStatus::GetGameClear())
	{
		mpMap->Draw();
		mpUIManager->DrawStatus(CGameStatus::GetScore(), mpMap->GetStep());

		if (mpMap->GetMaxEnemy() > 0)
			mpUIManager->DrawEnemyStatus(mpMap->GetNumEnemy());

		mpUIManager->DrawStageNum(mStage);
		mpUIManager->DrawMenu();

		if (mStageClear)
			mpStageClear->Draw();
	}

	if (CGameStatus::GetStageClear() == 1)
	{
		mpUIManager->FirstDrawHelp();

		if (CInput::GetKeyTrigger(VK_RETURN))
			mpUIManager->SetKeyEnter(true);
	}
}

void CStageManager::NextStage()
{
	mStage++;
	CGameStatus::SetStageClear(mStage);
	mStageClear = false;

	if (mStage > MaXStage)
		CGameStatus::SetGameClear(true);

	if (!CGameStatus::GetGameClear())
	{
		mpStageClear->SetMove();
		mpMap->Uninit();
		mpMap->Load(mStage);
		mpMap->Init();

		if (mpMap->GetMaxEnemy() > 0)
		{
			mpUIManager->Appear();
			mEnemyAppear = true;
		}
		else
			mEnemyAppear = false;
	}

	mPlusScore = false;

	CLoading::SetChange(false);
}

void CStageManager::ResetStage()
{
	mpMap->Uninit();
	mpMap->Load(mStage);
	mpMap->Init();

	mpUIManager->SetKeyEnter(false);

	CLoading::SetChange(false);
}

void CStageManager::ScoreCaculate()
{
	if (mStage >= CGameStatus::GetStageClear())
	{
		if (mStage * 100 - mpMap->GetStep() > 0)
			CGameStatus::PlusScore(mStage * 100 - mpMap->GetStep());
	}
	mPlusScore = true;
}