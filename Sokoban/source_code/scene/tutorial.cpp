using namespace std;


void CTutorial::Init()
{
	mTexture = "asset/texture/ui/key_info1.png";

	//�|�C���^�쐬
	mpPolygon = make_unique<CPolygon>();
	mpPolygon->Init(mTexture,XMFLOAT3(0.0f, 0.0f, LAYER6), SCREEN_WIDTH, SCREEN_HEIGHT);

	//���[�f�B���O�V�[���I��
	CLoading::SetChange(false);

	//�G���^�[�C���^�[�t�F�[�X�\��
	CEnter::SetEnable(true);
}

void CTutorial::Uninit()
{
	mpPolygon->Uninit();

	//�G���^�[�C���^�[�t�F�[�X��\��
	CEnter::SetEnable(false);
}

void CTutorial::Update()
{
	//���[�f�B���O�V�[���\��
	if (CInput::GetKeyTrigger(VK_RETURN))
		CLoading::SetEnable(true);

	//�V�[���`�F���W
	if (CLoading::GetChange())
		CSceneManager::SetScene<CStageSelect>();
}

void CTutorial::Draw()
{
	mpPolygon->Draw();
}