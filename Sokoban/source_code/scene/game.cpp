using namespace std;


void CGame::Init()
{
	//������ϊ�
	CAudioClip::Stop(CBGM::Start);
	CAudioClip::Play(true, CBGM::Game);

	//�J������ݒu
	AddGameObject<CCamera>()->Set(XMFLOAT3(3.0f, 5.0f, -7.0f));

	//�|�C���^�쐬
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

	//���[�f�B���O�V�[���I��
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

	//�Q�[���I�[�o�[����
	if (CGameStatus::GetGameOver())
	{
		CAudioClip::Stop(CBGM::Game);
		CAudioClip::Play(true, CBGM::End);

		mpGameOver->Update();

		//���o�I��
		if (mpGameOver->ShowEnd())
		{
			//���v���C���������A�����X�e�[�W�����Z�b�g
			if (CInput::GetKeyTrigger(VK_YEA))
			{
				mpStageManager->ResetStage();
				mpGameOver->SetKey(true);
				mGameOver = false;
			}
			//���v���C���Ȃ����A�Q�\���I�[�o�[
			else if (CInput::GetKeyTrigger(VK_NAY))
			{
				mpGameOver->SetKey(true);
				mGameOver = true;

			}
		}

		//�Q�[���I�[�o�[���o�����Z�b�g
		if (mpGameOver->GetKey() && mpGameOver->ResetShow())
		{
			mpGameOver->SetKey(false);

			if (!mGameOver)
			{
				CGameStatus::SetGameOver(false);
					
				//������ϊ�
				CAudioClip::Stop(CBGM::End);
				CAudioClip::Play(true, CBGM::Game);
			}
		}
	}

	//�^�E�Q�[���I�[�o�[
	if (CGameStatus::GetGameOver() && mGameOver)
	{
		//���[�f�B���O�V�[���\��
		CLoading::SetEnable(true);

		//�V�[���`�F���W
		if (CLoading::GetChange())
			CSceneManager::SetScene<CResult>();
	}

	//�V�[���`�F���W
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

		//�Q�[���I�[�o�[���o�I�����A���v���C�m�F�C���^�[�t�F�[�X�`��
		if (mpGameOver->ShowEnd())
			mpReplay->Draw();
	}
}

bool CGame::ReturnStageSelect()
{
	//�X�e�[�W�Z���N�g�֖߂�����
	if (mpStageManager->GetReturn())
	{
		//���[�f�B���O�V�[���\��
		if (CInput::GetKeyTrigger(VK_YEA))
			CLoading::SetEnable(true);

		//������
		else if (CInput::GetKeyTrigger(VK_NAY))
			mpStageManager->ReturnNay();

		//�V�[���`�F���W
		if (CLoading::GetChange())
			CSceneManager::SetScene<CStageSelect>(); return true;
	}
	return false;
}

bool CGame::ReturnTitle()
{
	//�^�C�g���֖߂�����
	if (mpStageManager->GetReturnTitle())
	{
		if (CInput::GetKeyTrigger(VK_YEA))
		{
			//���[�f�B���O�V�[���\��
			CLoading::SetEnable(true);

			//�������~
			CAudioClip::Stop(CBGM::Game);
		}
		//������
		else if (CInput::GetKeyTrigger(VK_NAY))
			mpStageManager->ReturnTitleNay();

		//�V�[���`�F���W
		if (CLoading::GetChange())
			CSceneManager::SetScene<CTitle>(); return true;
	}
	return false;
}