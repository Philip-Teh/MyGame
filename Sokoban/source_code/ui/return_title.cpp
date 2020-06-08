//using namespace UI;


CReturnTitle::CReturnTitle()
{
	mFile = "asset/texture/ui/returntitle.png";

	//�|�C���^�쐬
	mpPolygon = std::make_unique<CPolygon>();
	mpPolygon->Init(mFile, mWidth, mHeight);

	mMove = (int)SCREEN_HEIGHT;
	mKeyUpDown = mKeyUp = mKeyDown = false;
}

CReturnTitle::~CReturnTitle()
{
	mpPolygon->Uninit();

	OutputDebugString("delete CReturnTitle\n");
}

void CReturnTitle::Update()
{
	//�����L�[�ŊJ�����Ƃƕ��邱�Ƃ����s����
	//�J��
	if (!mKeyUpDown && CInput::GetKeyTrigger(VK_NUM4)) {
		mKeyUp = true;
		mKeyDown = false;
	}

	//����
	if (mKeyUpDown && CInput::GetKeyTrigger(VK_NUM4)) {
		mKeyDown = true;
		mKeyUp = false;
	}

	//�J���ړ�����
	if (!mKeyDown && mKeyUp && !mKeyUpDown) {
		mMove -= mSpeed;
		if (mMove <= 0)
			mKeyUpDown = true;
	}

	//����ړ�����
	if (mKeyDown && !mKeyUp && mKeyUpDown) {
		mMove += mSpeed;
		if (mMove >= SCREEN_HEIGHT)
			mKeyUpDown = false;
	}

	if (mMove <= 0)
		mMove = 0;

	if (mMove >= SCREEN_HEIGHT)
		mMove = SCREEN_HEIGHT;
}

void CReturnTitle::Draw()
{
	mpPolygon->Draw(XMFLOAT3(mPosition.x, mPosition.y + mMove, LAYER2));
}

void CReturnTitle::TabCancel(void)
{
	mKeyDown = true;
	mKeyUp = false;
	mMove += mSpeed;
}