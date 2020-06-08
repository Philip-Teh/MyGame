using namespace std;


void CStageManager::Init()
{
	//�|�C���^�쐬
	mpMap = make_unique<CMap>();
	mpUIManager = make_unique<CUIManager>();
	mpStageClear = make_unique<CStageClear>();
	mpStageOver = make_unique<CStageOver>();

	mStageClear = false;

	//�I�񂾃X�e�[�W��ۑ�
	mStage = CGameStatus::GetStageChoose();

	mpMap->Load(mStage);
	mpMap->Init();

	//�X�e�[�W�ɓG������ꍇ�A�G�̃C���^�[�t�F�[�X��\��
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
			//���j���[���쒆�ɃQ�[�����ꎞ��~
			if (!mpUIManager->GetPress()&& !mpUIManager->GetReset() && !mpUIManager->GetExit())
				mpMap->Update();

			mpUIManager->Update();
			mpUIManager->Update(mEnemyAppear);

			//�X�e�[�W���Z�b�g
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

		//�c�G���[���̎��A���������Ȃ��Ȃ�܂�
		if (mpMap->GetNumEnemy() == 0)
			mpUIManager->SetLock(true);
		else
			mpUIManager->SetLock(false);

		//�X�e�[�W�N���A���o
		if (mpMap->StageIsClear())
		{
			mStageClear = true;
			mpStageClear->Update();
		}
	}

	//�X�e�[�W�N���A���o��̃��[�f�B���O�V�[��
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

		//�X�e�[�W�ɓG�����݂��鎞�A�G�̐���`��
		if (mpMap->GetMaxEnemy() > 0)
			mpUIManager->DrawEnemyStatus(mpMap->GetNumEnemy());

		mpUIManager->DrawStageNum(mStage);
		mpUIManager->DrawMenu();

		//�X�e�[�W�N���A���o
		if (mStageClear)
			mpStageClear->Draw();

		//�X�e�[�W�I�[�o�[���o
		if (mpMap->GetStageIsOver())
			mpStageOver->Draw();
	}

	//�X�e�[�W�P�̃`���[�g���A��
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
	//�N���A�����X�e�[�W��ۑ�
	mStage++;
	CGameStatus::SetStageClear(mStage);

	mStageClear = false;

	//���o�̕`������Z�b�g
	mpStageClear->SetMove();

	//�X�e�[�W���ő���傫�����A�Q�[���N���A
	if (mStage > MaXStage)
		CGameStatus::SetGameClear(true);

	//�Q�[���N���A�ł͂Ȃ����A���̃X�e�[�W�����[�h
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
	//�I�񂾃X�e�[�W���N���A�����X�e�[�W���傫�����A�X�R�A�����Z
	if (mStage >= CGameStatus::GetStageClear())
	{
		if (mStage * 100 - mpMap->GetStep() > 0)
			CGameStatus::PlusScore(mStage * 100 - mpMap->GetStep());
	}
	mPlusScore = true;
}