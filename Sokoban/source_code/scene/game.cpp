using namespace std;


void CGame::Init()
{
	CAudioClip::Stop(CBGM::Start);
	CAudioClip::Play(true, CBGM::Game);

	//mpCamera = make_unique<CCamera>();
	//mpCamera->Init();
	//mpCamera->Set(XMFLOAT3(3.0f, 5.0f, -7.0f));

	AddGameObject<CCamera>()->Set(XMFLOAT3(3.0f, 5.0f, -7.0f));

	mpSkydome = make_unique<CSkydome>();
	mpSkydome->Init();

	mpMeshField = make_unique<CMeshfield>();
	mpMeshField->Init();

	//AddGameObject<CPolygon>(UI)->Create(mTexture, XMFLOAT3(SCREEN_WIDTH*0.45f, SCREEN_HEIGHT*0.4f, 0.0f), 100, 100);

	mpStageManager = make_unique<CStageManager>();
	mpStageManager->Init();


	mpGameOver = make_unique<CGameOver>();
	mpGameOver->Init();

	mpReplay = make_unique<CReplay>();
	mGameOver = false;

	CLoading::SetChange(false);
}

void CGame::Uninit()
{
	//mpCamera->Uninit();
	mpSkydome->Uninit();
	mpMeshField->Uninit();
	mpStageManager->Uninit();

	mpGameOver->Uninit();

	CScene::Uninit();
}

void CGame::Update()
{
	CLoading::GetChange();

	//mpCamera->Update();
	mpSkydome->Update();
	mpMeshField->Update();
	mpStageManager->Update();

	CScene::Update();

	CLoading::GetChange();
	
	if (ReturnStageSelect())return;
	if (ReturnTitle())return;

	if (CGameStatus::GetGameOver())
	{
		CAudioClip::Stop(CBGM::Game);
		CAudioClip::Play(true, CBGM::End);

		mpGameOver->Update();

		if (mpGameOver->ShowEnd())
		{
			if (CInput::GetKeyTrigger(VK_YEA))
			{
				mpStageManager->ResetStage();
				mpGameOver->SetKey(true);
				mGameOver = false;
			}
			else if (CInput::GetKeyTrigger(VK_NAY))
			{
				mpGameOver->SetKey(true);
				mGameOver = true;

			}
		}
		if (mpGameOver->GetKey() && mpGameOver->ResetShow())
		{
			mpGameOver->SetKey(false);

			if (!mGameOver)
			{
				CGameStatus::SetGameOver(false);

				CAudioClip::Stop(CBGM::End);
				CAudioClip::Play(true, CBGM::Game);
			}
		}
	}

	if (CGameStatus::GetGameOver() && mGameOver)
	{
		CLoading::SetEnable(true);

		if (CLoading::GetChange())
			CSceneManager::SetScene<CResult>();
	}

	if (CGameStatus::GetGameClear())
		CSceneManager::SetScene<CGameClear>();		
}

void CGame::Draw()
{
	//mpCamera->Draw();
	mpSkydome->Draw();
	mpMeshField->Draw();
	mpStageManager->Draw();

	if (CGameStatus::GetGameOver())
	{
		mpGameOver->Draw();

		if (mpGameOver->ShowEnd())
			mpReplay->Draw();
	}
}

bool CGame::ReturnStageSelect()
{
	if (mpStageManager->GetReturn())
	{
		if (CInput::GetKeyTrigger(VK_YEA))
			CLoading::SetEnable(true);
		else if (CInput::GetKeyTrigger(VK_NAY))
			mpStageManager->ReturnNay();

		if (CLoading::GetChange())
			CSceneManager::SetScene<CStageSelect>(); return true;
	}
	return false;
}

bool CGame::ReturnTitle()
{
	if (mpStageManager->GetReturnTitle())
	{
		if (CInput::GetKeyTrigger(VK_YEA))
		{
			CLoading::SetEnable(true);
			CAudioClip::Stop(CBGM::Game);
		}
		else if (CInput::GetKeyTrigger(VK_NAY))
			mpStageManager->ReturnTitleNay();

		if (CLoading::GetChange())
			CSceneManager::SetScene<CTitle>(); return true;
	}
	return false;
}