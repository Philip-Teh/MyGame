using namespace std;


void CNumDraw::Init(float sizeX, float sizeY)
{
	mTexture = "asset/texture/number/number.png";

	//ポインタ作成
	mpNumber = make_unique<CNumber>();
	mpNumber->Init(mTexture, sizeX, sizeY);

	mDigit = NUMBER_DIGIT;

	//描画最大数を計算
	mCounterStop = 1;

	for (int i = 0;i < mDigit;i++)
	{
		mCounterStop *= 10;
	}
	mCounterStop--;
}

void CNumDraw::InitGreen(float sizeX, float sizeY)
{
	mTexture = "asset/texture/number/numbergreen.png";

	//ポインタ作成
	mpNumber = make_unique<CNumber>();
	mpNumber->Init(mTexture, sizeX, sizeY);

	mDigit = NUMBER_DIGIT;

	//描画最大数を計算
	mCounterStop = 1;

	for (int i = 0; i < mDigit; i++)
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

	//数値の右から描画
	for (int i = 0;i < digit;i++)
	{
		mpNumber->Draw(XMFLOAT3(position.x - (float)NUMBER_WIDTH*i, position.y,position.z), num % 10);

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

	//数値の右から描画
	for (int i = 0; i < digit; i++)
	{
		mpNumber->Draw(XMFLOAT3(position.x - (float)NUMBER_WIDTH * i, position.y, position.z), num % 10, tw, th);

		num /= 10;
	}
}