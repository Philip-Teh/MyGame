using namespace std;

void CEffect::Init(std::string texture,XMFLOAT2 size,int patternmax)
{
	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);

	//�|�C���^�쐬
	mpBillBoard = make_unique<CBillBoard>();
	mpBillBoard->Init(texture, size);

	mEnable = false;
	mFrameCount = 0;
	mCreateFrame = 0;
	mPatternCount = 0;

	mPatternMax = patternmax;

	mSize.x = (int)size.x;
	mSize.y = (int)size.y;
}

void CEffect::Uninit()
{
	mpBillBoard->Uninit();

	OutputDebugString("delete CEffect\n");
}

void CEffect::Update()
{
	if (mEnable)
	{
		//�G�t�F�N�g�̑��ݎ��Ԃ��v�Z
		int age = mFrameCount - mCreateFrame;
		mPatternCount = age / mPatternMax;

		//���Ԃ𒴂�����A�����ɂ���
		if (mPatternCount >= mPatternMax)
			mEnable = false;

		mFrameCount++;
	}
}

void CEffect::Draw()
{
	if (mEnable)
	{
		//�摜�p�^�[������
		int tx = mSize.x / mPatternMax * (mPatternCount % mPatternMax);
		int ty = mSize.y * (mPatternCount / mPatternMax);

		mpBillBoard->Draw(m_Position, tx, ty, mSize.x / mPatternMax, mSize.y);
	}
}

void CEffect::Create(XMFLOAT3 position)
{
	m_Position.x = position.x;
	m_Position.y = -2.0f;
	m_Position.z = (position.z + 2.0f) * -1;
	//mFrameCount = 0;
	mEnable = true;
}