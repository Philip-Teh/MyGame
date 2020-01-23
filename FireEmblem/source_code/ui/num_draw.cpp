using namespace std;


void CNumDraw::Init(int digit, float sizeX, float sizeY)
{
	mpNumber = make_unique<CNumber>();
	mpNumber->Init(sizeX, sizeY);

	mDigit = digit;

	mCounterStop = 1;

	for (int i = 0;i < digit;i++)
	{
		mCounterStop *= 10;
	}
	mCounterStop--;
}

void CNumDraw::Uninit(void)
{
	mpNumber->Uninit();
}

void CNumDraw::Draw(XMFLOAT3 position, int score)
{
	//カウンターストップ(カンスト処理)
	if (score >= mCounterStop)
	{
		score = mCounterStop;
	}

	for (int i = mDigit - 1;i >= 0;i--)
	{
		mpNumber->Draw(XMFLOAT3(position.x + NUMBER_WIDTH*i, position.y,position.z), score % 10);

		score /= 10;
	}
}