using namespace std;


void CStageManager::Init()
{
	//ポインタ作成
	mpMap = make_unique<CMap>();
	mpUIManager = make_unique<CUIManager>();
	mpStageClear = make_unique<CStageClear>();
	mpStageOver = make_unique<CStageOver>();

	mStageClear = false;

	//選んだステージを保存
	mStage = CGameStatus::GetStageChoose();

	mpMap->Load(mStage);
	mpMap->Init();

	//ステージに敵がいる場合、敵のインターフェースを表示
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
			//メニュー操作中にゲームを一時停止
			if (!mpUIManager->GetPress()&& !mpUIManager->GetReset() && !mpUIManager->GetExit())
				mpMap->Update();

			mpUIManager->Update();
			mpUIManager->Update(mEnemyAppear);

			//ステージリセット
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

		//残敵がゼロの時、箱を引けなくなります
		if (mpMap->GetNumEnemy() == 0)
			mpUIManager->SetLock(true);
		else
			mpUIManager->SetLock(false);

		//ステージクリア演出
		if (mpMap->StageIsClear())
		{
			mStageClear = true;
			mpStageClear->Update();
		}
	}

	//ステージクリア演出後のローディングシーン
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

		//ステージに敵が存在する時、敵の数を描画
		if (mpMap->GetMaxEnemy() > 0)
			mpUIManager->DrawEnemyStatus(mpMap->GetNumEnemy());

		mpUIManager->DrawStageNum(mStage);
		mpUIManager->DrawMenu();

		//ステージクリア演出
		if (mStageClear)
			mpStageClear->Draw();

		//ステージオーバー演出
		if (mpMap->GetStageIsOver())
			mpStageOver->Draw();
	}

	//ステージ１のチュートリアル
	if (CGameStatus::GetStageClear() == 1)
	{
		if (!mStageClear)
			mpUIManager->FirstDrawCancel();

		mpUIManager->FirstDrawHelp();

		if (CInput::GetKeyTrigger(VK_RETURN))
		{
			mpUIManager->SetKeyEnter(true);
		}
	}
}

void CStageManager::NextStage()
{
	//クリアしたステージを保存
	mStage++;
	CGameStatus::SetStageClear(mStage);

	mStageClear = false;

	//演出の描画をリセット
	mpStageClear->SetMove();

	//ステージが最大より大きい時、ゲームクリア
	if (mStage > MaXStage)
		CGameStatus::SetGameClear(true);

	//ゲームクリアではない時、次のステージをロード
	if (!CGameStatus::GetGameClear())
	{
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

	CLoading::SetChange(false);
}

void CStageManager::ScoreCaculate()
{
	//選んだステージがクリアしたステージより大きい時、スコアを加算
	if (mStage >= CGameStatus::GetStageClear())
	{
		if (mStage * 100 - mpMap->GetStep() > 0)
			CGameStatus::PlusScore(mStage * 100 - mpMap->GetStep());
	}
	mPlusScore = true;
}