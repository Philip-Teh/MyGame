using namespace std;
//using namespace UI;

CUIManager::CUIManager()
{
	//�|�C���^�쐬
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

	//���j���[���쒆
	if (mpMenu->GetKeyUp())
	{
		mpHelp->Update();
		mpKeyInfo->Update();
		mpTitle->Update();
		mpReturn->Update();
	}

	//���j���[�ޏo���ɑS�ẴC���^�[�t�F�[�X���I��
	if (mpMenu->GetKeyDown())
	{
		mpHelp->TabCancel();
		mpKeyInfo->TabCancel();
		mpTitle->TabCancel();
		mpReturn->TabCancel();
	}

	mpReset->Update();

	mpExit->Update();

	//�Q�[���ޏo���Ɋm�F�C���^�[�t�F�[�X��\��
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

//�X�R�A�ƃX�e�b�v�̕`��
void CUIManager::DrawStatus(int score,int step)
{
	mpScore->Draw(score);
	mpStep->Draw(step);
}

//�G�ƈ������̕`��
void CUIManager::DrawEnemyStatus(int num)
{
	mpNumEnemy->Draw(num);
	mpPull->Draw();
}

//�X�e�[�W�i���o�[�`��
void CUIManager::DrawStageNum(int num)
{
	mpStageNum->Draw(num);
}

//���j���[�`��
void CUIManager::DrawMenu()
{
	//���j���[���쎞�ɃQ�[���ꎞ��~��ʂ�`��
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

//�B���C���^�[�t�F�[�X��`��
void CUIManager::Appear()
{
	mpNumEnemy->Appear();
	mpPull->Appear();
}