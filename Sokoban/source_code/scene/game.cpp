using namespace std;


void CGame::Init()
{
	//音声を変換
	CAudioClip::Stop(CBGM::Start);
	CAudioClip::Play(true, CBGM::Game);

	//カメラを設置
	AddGameObject<CCamera>()->Set(XMFLOAT3(3.0f, 5.0f, -7.0f));

	//ポインタ作成
	mpSkydome = make_unique<CSkydome>();
	mpSkydome->Init();

	mpMeshField = make_unique<CMeshfield>();
	mpMeshField->Init();

	mpStageManager = make_unique<CStageManager>();
	mpStageManager->Init();

	mpGameOver = make_unique<CGameOver>();
	mpGameOver->Init();

	mpReplay = make_unique<CReplay>();
	mGameOver = false;

	//ローディングシーン終了
	CLoading::SetChange(false);
}

void CGame::Uninit()
{
	mpSkydome->Uninit();
	mpMeshField->Uninit();
	mpStageManager->Uninit();

	mpGameOver->Uninit();

	CScene::Uninit();
}

void CGame::Update()
{
	mpSkydome->Update();
	mpMeshField->Update();
	mpStageManager->Update();

	CScene::Update();
	
	if (ReturnStageSelect())return;
	if (ReturnTitle())return;

	//ゲームオーバー処理
	if (CGameStatus::GetGameOver())
	{
		CAudioClip::Stop(CBGM::Game);
		CAudioClip::Play(true, CBGM::End);

		mpGameOver->Update();

		//演出終了
		if (mpGameOver->ShowEnd())
		{
			//リプレイしたい時、同じステージをリセット
			if (CInput::GetKeyTrigger(VK_YEA))
			{
				mpStageManager->ResetStage();
				mpGameOver->SetKey(true);
				mGameOver = false;
			}
			//リプレイしない時、ゲ―ムオーバー
			else if (CInput::GetKeyTrigger(VK_NAY))
			{
				mpGameOver->SetKey(true);
				mGameOver = true;

			}
		}

		//ゲームオーバー演出をリセット
		if (mpGameOver->GetKey() && mpGameOver->ResetShow())
		{
			mpGameOver->SetKey(false);

			if (!mGameOver)
			{
				CGameStatus::SetGameOver(false);
					
				//音声を変換
				CAudioClip::Stop(CBGM::End);
				CAudioClip::Play(true, CBGM::Game);
			}
		}
	}

	//真・ゲームオーバー
	if (CGameStatus::GetGameOver() && mGameOver)
	{
		//ローディングシーン表示
		CLoading::SetEnable(true);

		//シーンチェンジ
		if (CLoading::GetChange())
			CSceneManager::SetScene<CResult>();
	}

	//シーンチェンジ
	if (CGameStatus::GetGameClear())
		CSceneManager::SetScene<CGameClear>();		
}

void CGame::Draw()
{
	mpSkydome->Draw();
	mpMeshField->Draw();
	mpStageManager->Draw();

	if (CGameStatus::GetGameOver())
	{
		mpGameOver->Draw();

		//ゲームオーバー演出終了時、リプレイ確認インターフェース描画
		if (mpGameOver->ShowEnd())
			mpReplay->Draw();
	}
}

bool CGame::ReturnStageSelect()
{
	//ステージセレクトへ戻す処理
	if (mpStageManager->GetReturn())
	{
		//ローディングシーン表示
		if (CInput::GetKeyTrigger(VK_YEA))
			CLoading::SetEnable(true);

		//取り消し
		else if (CInput::GetKeyTrigger(VK_NAY))
			mpStageManager->ReturnNay();

		//シーンチェンジ
		if (CLoading::GetChange())
			CSceneManager::SetScene<CStageSelect>(); return true;
	}
	return false;
}

bool CGame::ReturnTitle()
{
	//タイトルへ戻す処理
	if (mpStageManager->GetReturnTitle())
	{
		if (CInput::GetKeyTrigger(VK_YEA))
		{
			//ローディングシーン表示
			CLoading::SetEnable(true);

			//音声を停止
			CAudioClip::Stop(CBGM::Game);
		}
		//取り消し
		else if (CInput::GetKeyTrigger(VK_NAY))
			mpStageManager->ReturnTitleNay();

		//シーンチェンジ
		if (CLoading::GetChange())
			CSceneManager::SetScene<CTitle>(); return true;
	}
	return false;
}