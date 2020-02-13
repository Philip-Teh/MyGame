using namespace std;


void CNumDraw::Init(float sizeX, float sizeY)
{
	mpNumber = make_unique<CNumber>();
	mpNumber->Init(sizeX, sizeY);

	mDigit = NUMBER_DIGIT;

	mCounterStop = 1;

	for (int i = 0;i < mDigit;i++)
	{
		mCounterStop *= 10;
	}
	mCounterStop--;
}

void CNumDraw::Uninit(void)
{
	mpNumber->Uninit();
}

void CNumDraw::Draw(XMFLOAT3 position, int num)
{
	//カウンターストップ(カンスト処理)
	if (num >= mCounterStop)
		num = mCounterStop;

	if (num <= 0)
		num = 0;

	int digit = mpNumber->GetDigit(num);

	for (int i = 0;i < digit;i++)
	{
		mpNumber->Draw(XMFLOAT3(position.x - NUMBER_WIDTH*i, position.y,position.z), num % 10);

		num /= 10;
	}
}

void CNumDraw::Draw(XMFLOAT3 position, int num,int tw,int th)
{
	//カウンターストップ(カンスト処理)
	if (num >= mCounterStop)
		num = mCounterStop;

	if (num <= 0)
		num = 0;

	int digit = mpNumber->GetDigit(num);

	for (int i = 0; i < digit; i++)
	{
		mpNumber->Draw(XMFLOAT3(position.x - NUMBER_WIDTH * i, position.y, position.z), num % 10, tw, th);

		num /= 10;
	}
}