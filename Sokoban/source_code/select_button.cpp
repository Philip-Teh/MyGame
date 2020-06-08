using namespace std;

CSelectButton::CSelectButton()
{
	//選択インターフェース
	mTexture[0] = "asset/texture/ui/button0.png";

	//未開放インターフェース
	mTexture[1] = "asset/texture/ui/gray.png";

	for (int i = 0; i < BUTTON + 2; i++)
		mpPolygon[i] = make_unique<CPolygon>();

	mpPolygon[0]->Init(mTexture[0], mSize, mSize);
	mpPolygon[BUTTON + 1]->Init(mTexture[1], mSize, mSize);

	//ステージボタン読み込み
	for (int i = 1; i <= BUTTON; i++)
	{
		sprintf_s(mFilename, "asset/texture/number/button%d.png", i);
		mpPolygon[i]->Init(mFilename, mSize, mSize);

		mClear[i] = false;
	}

	//選択中のボタン
	mChoose = 1;

	//クリアしたステージを保存
	for (int i = 1; i <= CGameStatus::GetStageClear(); i++)
		mClear[i] = true;
}

CSelectButton::~CSelectButton()
{
	for (int i = 0; i < BUTTON + 2; i++)
		mpPolygon[i]->Uninit();

	OutputDebugString("delete CSelectButton\n");
}

void CSelectButton::Update()
{
	//キーによって選択インターフェースを移動
	KeyInput();

	//ステージを選択
	if (mClear[mChoose] == true)
		CGameStatus::SetStageChoose(mChoose);
}

void CSelectButton::Draw()
{
	//ボタンを描画
	for (int i = 1; i <= BUTTON; i++)
	{
		float y = 0.0f;
		int x = 0;

		if (i > mButtonX)
		{
			x = mButtonX;
			y = mSpace;
		}

		mpPolygon[i]->Draw(XMFLOAT3(mPositionX * (i - x) + (i - x - 1) * mSize, mPositionY + y, LAYER5));

		//クリアステージ以外のボタンに未開放インターフェースを重なって描画
		if (!mClear[i])
			mpPolygon[BUTTON + 1]->Draw(XMFLOAT3(mPositionX * (i - x) + (i - x - 1) * mSize, mPositionY + y, LAYER4));
	}

	float y = 0.0f;
	int x = 0;

	if (mChoose > mButtonX)
	{
		x = mButtonX;
		y = mSpace;
	}

	//選択インターフェース描画
	mpPolygon[0]->Draw(XMFLOAT3(mPositionX * (mChoose - x) + (mChoose - x - 1) * mSize, mPositionY + y, LAYER4));
}

void CSelectButton::KeyInput(void)
{
	if (mChoose + 1 <= BUTTON && mClear[mChoose + 1])
		if (CInput::GetKeyTrigger('D') || CInput::GetKeyTrigger(VK_RIGHT))
			mChoose++;

	if (mChoose - 1 > 0 && mClear[mChoose - 1])
		if (CInput::GetKeyTrigger('A') || CInput::GetKeyTrigger(VK_LEFT))
			mChoose--;

	if (mChoose + 5 <= BUTTON && mClear[mChoose + 5])
		if (CInput::GetKeyTrigger('S') || CInput::GetKeyTrigger(VK_DOWN))
			mChoose += 5;

	if (mChoose - 5 > 0 && mClear[mChoose - 5])
		if (CInput::GetKeyTrigger('W') || CInput::GetKeyTrigger(VK_UP))
			mChoose -= 5;
}