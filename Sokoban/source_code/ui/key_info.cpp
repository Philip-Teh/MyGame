//using namespace UI;


CKeyInfo::CKeyInfo()
{
	mFile = "asset/texture/ui/key_info1.png";

	//�|�C���^�쐬
	mpPolygon = std::make_unique<CPolygon>();
	mpPolygon->Init(mFile, SCREEN_WIDTH, SCREEN_HEIGHT);

	mMove = (int)SCREEN_HEIGHT;
	mKeyUpDown = mKeyUp = mKeyDown = false;
}

CKeyInfo::~CKeyInfo()
{
	mpPolygon->Uninit();

	OutputDebugString("delete CKeyInfo\n");
}

void CKeyInfo::Update()
{
	//�����L�[�ŊJ�����Ƃƕ��邱�Ƃ����s����
	//�J��
	if (!mKeyUpDown && CInput::GetKeyTrigger(VK_NUM2)) {
		mKeyUp = true;
		mKeyDown = false;
	}

	//����
	if (mKeyUpDown && CInput::GetKeyTrigger(VK_NUM2)) {
		mKeyDown = true;
		mKeyUp = false;
	}

	//�J���ړ�����
	if (!mKeyDown && mKeyUp && !mKeyUpDown) {
		mMove -= 100;
		if (mMove <= 0)
			mKeyUpDown = true;
	}

	//����ړ�����
	if (mKeyDown && !mKeyUp && mKeyUpDown) {
		mMove += 100;
		if (mMove >= SCREEN_HEIGHT)
			mKeyUpDown = false;
	}

	if (mMove <= 0)
		mMove = 0;
	if (mMove >= SCREEN_HEIGHT)
		mMove = SCREEN_HEIGHT;
}

void CKeyInfo::Draw()
{
	mpPolygon->Draw(XMFLOAT3(0.0f, 0.0f + mMove, LAYER1));
}

void CKeyInfo::TabCancel(void)
{
	mKeyDown = true;
	mKeyUp = false;
	mMove += 100;
}