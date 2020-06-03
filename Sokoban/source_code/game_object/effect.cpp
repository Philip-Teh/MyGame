using namespace std;

void CEffect::Init(std::string texture,XMFLOAT2 size,int patternmax)
{
	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	/*m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);*/

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
		int age = mFrameCount - mCreateFrame;
		mPatternCount = age / mPatternMax;

		if (mPatternCount >= mPatternMax)
			mEnable = false;

		mFrameCount++;
	}
}

void CEffect::Draw()
{
	if (mEnable)
	{
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